#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

uint64_t fib(uint64_t n) {
  if (n < 2) { 
    return n; 
  } else {
    uint64_t x = fib(n-1);
    uint64_t y = fib(n-2);  
    return (x + y);
  }
}

typedef struct {
  uint64_t input;
  uint64_t output;
} thread_args;

void *thread_func(void *ptr) {
  uint64_t i = 
    ((thread_args *) ptr)->input;
  ((thread_args *) ptr)->output = fib(i);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t thread;
  thread_args args;
  int status;
  uint64_t result;

  if (argc < 2) { return 1; }
  uint64_t n = strtoul(argv[1], NULL, 0);
  if (n < 30) {
	result = fib(n);
  } else {
    args.input = n-1;
    status = pthread_create(&thread, 
                            NULL, 
                            thread_func, 
                            (void*) &args);
    // main can continue executing
    result = fib(n-2);
    // Wait for the thread to terminate.
    status = pthread_join(thread, NULL);
    result += args.output;
  }
  printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n",   
         n, result);
  return 0;
}

