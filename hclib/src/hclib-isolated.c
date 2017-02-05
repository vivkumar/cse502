/* Copyright (c) 2015, Rice University

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

1.  Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above
     copyright notice, this list of conditions and the following
     disclaimer in the documentation and/or other materials provided
     with the distribution.
3.  Neither the name of Rice University
     nor the names of its contributors may be used to endorse or
     promote products derived from this software without specific
     prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

/*
 * hclib-isolated.c
 *
 *      Author: Vivek Kumar (vivekk@rice.edu)
 *      Acknowledgments: https://wiki.rice.edu/confluence/display/HABANERO/People
 */

#include <stdio.h>
#include "hclib-internal.h"
#include <stdbool.h>
#include <stdlib.h>
#include "hashmap.h"

//#define DISPLAY_COLLISIONS
#define INITIAL_HASHMAP_SIZE 1048576
#define KNUTH_CONSTANT 2654435761
static Hashmap* isolated_map = NULL;

/* Support for global isolation in HClib ------> */
static volatile int global_isolation_mutex = UNLOCK_VAL;
#define GLOBAL_ISOLATION_LOCK CAS_LOCK(&global_isolation_mutex)
#define GLOBAL_ISOLATION_UNLOCK CAS_UNLOCK(&global_isolation_mutex)
/* <------ Support for global isolation in HClib */

// TODO: Find a better hash function
// When using knuth constant in multiplication
// there might be integer overflow, so not using
// that at moment. The hashmap implementation
// copied from Android project operates on 
// int hash only, hence currently typecasting
// to int. Although its not safe to typecast pointers to int
static int hash(void * ptr) {
#if 0
  // Knuth's multiplicative hash
  // This hash function also being used in qthreads:
  // https://github.com/Qthreads/qthreads/blob/qtCnC/cnc/cnc.h
  return (((int)ptr) * KNUTH_CONSTANT);
#else
  return (int)ptr;
#endif
}

static bool equals(void* a, void* b) {
  return (a == b);
}

/*
 * Initialize the datastructures required for isolation implementation
 */
void init_isolation_datastructures() {
  isolated_map = hashmapCreate(INITIAL_HASHMAP_SIZE, hash, equals);
  HASSERT(isolated_map);
}

/*
 * Finalize the datastructures used in isolation implementation
 */
void finalize_isolation_datastructure() {
#ifdef DISPLAY_COLLISIONS
  printf("HCLIB_DEBUG_MESSAGE: total collisions in isolation hashmap was %zu\n",hashmapCountCollisions(isolated_map));
  printf("HCLIB_DEBUG_MESSAGE: turn off this report with DISPLAY_COLLISIONS macro\n");
#endif
  hashmapFree(isolated_map); 
  isolated_map = NULL;
}

/*
 * Used in sorting the hashmap entries based on index value
 */
int compare_index(const void* e1, const void* e2) {
  const Entry** entry1 = (Entry**) e1;
  const Entry** entry2 = (Entry**) e2;
  return ((*entry1)->index > (*entry2)->index);
}

/****************************************
 **** USER INTERFACES *****
 ***************************************/

/*
 * User registers the objects that would
 * require isolation
 * 
 * Note: This method is to be called on single thread
 */
void apply_isolation(void** array, int n) {
  int i;
  hashmapLock(isolated_map);
  for(i=0; i<n; i++) {
    const void* ptr = array[i];
    hashmapPut(isolated_map, ptr, NULL);
  }
  hashmapUnlock(isolated_map);
}

/*
 * User de-registers the objects that would
 * require isolation.
 * 
 * Note: This method is to be called on single thread
 */
void remove_isolation(void** array, int n) {
  int i;
  hashmapLock(isolated_map);
  for(i=0; i<n; i++) {
    const void* ptr = array[i];
    hashmapRemove(isolated_map, ptr);
  }
  hashmapUnlock(isolated_map);
}

/*
 * User calls this method to request a global isolation
 * that is achieved using a global mutex lock. This is
 * similar to OpenMP critical section
 */
void global_isolatation(generic_frame_ptr func, void *args) {
    GLOBAL_ISOLATION_LOCK;
    // execute the critical section
    func(args);
    GLOBAL_ISOLATION_UNLOCK;
}

/*
 * User calls this method to request isolation on set of objects
 */
void isolated_execution(void** object, int total, generic_frame_ptr func, void *args) {
  int i;
  if(total == 1) {
    // find Entry and acquire lock first
    const Entry* e = hashmapGetEntry(isolated_map, *object);
    CAS_LOCK(e->value);
    // Now launch the lambda function
    func(args);
    // Release locks acquired
    CAS_UNLOCK(e->value);
  }
  else {
    Entry* array[total];
    // retreive key/value pair from hashmap first
    for(i=0; i<total; i++) {
      array[i] = hashmapGetEntry(isolated_map, object[i]);
    }
    // sort the array based on index value
    // For explanation, see header file hashmap_extension.h
    qsort(array, total, sizeof(Entry*), compare_index);
    // Acquire lock in the order they are stored in this array
    for(i=0; i<total; i++) {
      CAS_LOCK(array[i]->value);
    }
    // Now launch the lambda function
    func(args);
    // Atomic section is executed and hence release all locks
    // Release locks in the order they were acquired
    for(i=0; i<total; i++) {
      CAS_UNLOCK(array[i]->value);
    }
  }
}

