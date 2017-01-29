#include "hclib_cpp.h"
#include <inttypes.h>
#include <sys/time.h>

#define CACHE_LINE_SIZE 64
uint64_t* total_asyncs;
#define MY_INDEX (hclib::current_worker() * CACHE_LINE_SIZE)

long get_usecs (void)
{
   struct timeval t;
   gettimeofday(&t,NULL);
   return t.tv_sec*1000000+t.tv_usec;
}

uint64_t fib_seq(int n) {
  if (n < 2) {
    return n;
  }
  else {
    return fib_seq(n-1) + fib_seq(n-2);
  }
}

uint64_t fib(uint64_t n) {
  if (n < 10) { 
    return fib_seq(n);
  } 
  else {
    uint64_t x, y;
    hclib::finish([&]() {
      hclib::async([&]() {
        // as this is an async task, increment the counter at my index in the array
        total_asyncs[MY_INDEX]++;
        x = fib(n-1);
      });
      y = fib(n-2);
    }); 
    return (x + y);
  }
}

int main(int argc, char **argv) {
  hclib::launch([&]() {
    if (argc < 2) { return 1; }
    uint64_t n = strtoul(argv[1], NULL, 0);
    // Allocate the array with size as total number of HCLIB_WORKERS 
    total_asyncs = new uint64_t[hclib::num_workers() * CACHE_LINE_SIZE];
    // initalize the array
    for(int i=0; i<hclib::num_workers(); i++) {
        total_asyncs[i*CACHE_LINE_SIZE] = 0;
    }
    long start = get_usecs();
    uint64_t result = fib(n);
    long end = get_usecs();
    double dur = ((double)(end-start))/1000000;
    printf("Fibonacci of %" PRIu64 " is %" PRIu64 ". Time = %.3f sec\n", n, result, dur);
    uint64_t total=0;
    for(int i=0; i<hclib::num_workers(); i++) total += total_asyncs[i*CACHE_LINE_SIZE]; 
    printf("Total asyncs spawned = %" PRIu64 "\n",total);
    delete (total_asyncs);
  });
  return 0; 
}
