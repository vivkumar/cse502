/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Hash map.
 */

#ifndef __HASHMAP_H
#define __HASHMAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Vivek Kumar:
 * Locking and unlocking is implemented using GCC builtin Atomic Operations
 * in isolated construct. Default value of a lock/unlocked object is defined here
 * as macros -------------------->
 */
//default value for unlocked variable
#define UNLOCK_VAL 0
//default value for locked variable
#define LOCK_VAL 1
// locking macro
#define CAS_LOCK(p) {while(!__sync_bool_compare_and_swap(p, UNLOCK_VAL, LOCK_VAL));}
// unlocking macro
#define CAS_UNLOCK(p) {*p = UNLOCK_VAL;} 
/* <---------------------*/

/** A hash map. */
typedef struct Hashmap Hashmap;
/* A key/value entry in hasmap */
typedef struct Entry Entry;
struct Entry {
    void* key;
    int hash;
    volatile int* value;
/*
 * Added to support indexing. See hashmap_extension.h for further details.
 */
    uint64_t index;
    Entry* next;
};

/**
 * Creates a new hash map. Returns NULL if memory allocation fails.
 *
 * @param initialCapacity number of expected entries
 * @param hash function which hashes keys
 * @param equals function which compares keys for equality
 */
Hashmap* hashmapCreate(size_t initialCapacity,
        int (*hash)(void* key), bool (*equals)(void* keyA, void* keyB));

/**
 * Frees the hash map. Does not free the keys or values themselves.
 */
void hashmapFree(Hashmap* map);

/**
 * Puts value for the given key in the map. Returns pre-existing value if
 * any.
 *
 * If memory allocation fails, this function returns NULL, the map's size
 * does not increase, and errno is set to ENOMEM.
 */
void* hashmapPut(Hashmap* map, void* key, void* value);

/**
 * Gets a value from the map. Returns NULL if no entry for the given key is
 * found or if the value itself is NULL.
 */
// Direct access not allowed
// void* hashmapGet(Hashmap* map, void* key);

/*
 * Added to support indexing. See hashmap_extension.h for further details.
 */
Entry* hashmapGetEntry(Hashmap* map, void* key);

/**
 * Removes an entry from the map. Returns the removed value or NULL if no
 * entry was present.
 */
void* hashmapRemove(Hashmap* map, void* key);

/**
 * Gets the number of entries in this map.
 */
size_t hashmapSize(Hashmap* map);

/**
 * Concurrency support.
 */

/**
 * Locks the hash map so only the current thread can access it.
 */
void hashmapLock(Hashmap* map);

/**
 * Unlocks the hash map so other threads can access it.
 */
void hashmapUnlock(Hashmap* map);

/*
 * vivekk: All these functions are currently unused in hclib. Hence, they
 * are still containing the default downloaded code. If you have to use this function
 * then change the entry->value as we updated it to a scalar from a pointer.
 */
#if 0

/**
 * Returns true if the map contains an entry for the given key.
 */
bool hashmapContainsKey(Hashmap* map, void* key);

/**
 * Hashes the memory pointed to by key with the given size. Useful for
 * implementing hash functions.
 */
int hashmapHash(void* key, size_t keySize);

/**
 * Gets the value for a key. If a value is not found, this function gets a 
 * value and creates an entry using the given callback.
 *
 * If memory allocation fails, the callback is not called, this function
 * returns NULL, and errno is set to ENOMEM.
 */
void* hashmapMemoize(Hashmap* map, void* key, 
        void* (*initialValue)(void* key, void* context), void* context);

/**
 * Invokes the given callback on each entry in the map. Stops iterating if
 * the callback returns false.
 */
void hashmapForEach(Hashmap* map, 
        bool (*callback)(void* key, void* value, void* context),
        void* context);

/**
 * Key utilities.
 */

/**
 * Hashes int keys. 'key' is a pointer to int.
 */
int hashmapIntHash(void* key);

/**
 * Compares two int keys for equality.
 */
bool hashmapIntEquals(void* keyA, void* keyB);

/**
 * For debugging.
 */

/**
 * Gets current capacity.
 */
size_t hashmapCurrentCapacity(Hashmap* map);

/**
 * Counts the number of entry collisions.
 */
size_t hashmapCountCollisions(Hashmap* map);

#endif //<------------ unused functions till here

#ifdef __cplusplus
}
#endif

#endif /* __HASHMAP_H */ 
