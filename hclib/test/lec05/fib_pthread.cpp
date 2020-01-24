#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

long get_usecs (void)
{
     struct timeval t;
        gettimeofday(&t,NULL);
           return t.tv_sec*1000000+t.tv_usec;
}

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
  double dur;
  uint64_t result;

  if (argc < 2) { return 1; }
  uint64_t n = strtoul(argv[1], NULL, 0);
  if (n < 30) {
	result = fib(n);
  } else {
    args.input = n-1;
    long start = get_usecs();
    status = pthread_create(&thread, 
                            NULL, 
                            thread_func, 
                            (void*) &args);
    // main can continue executing
    result = fib(n-2);
    // Wait for the thread to terminate.
    status = pthread_join(thread, NULL);
    result += args.output;
    long end = get_usecs();
    dur = ((double)(end-start))/1000000;
  }
  printf("Fibonacci of %" PRIu64 " is %" PRIu64 "Time = %.2f.\n",   
         n, result,dur);
  return 0;
}

