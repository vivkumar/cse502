#include "hclib_cpp.h"
#include <inttypes.h>
#include <sys/time.h>

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
  if (n < 12) { 
    return fib_seq(n);
  } else {
    uint64_t x, y;
    hclib::finish([&]() {
      hclib::async([&]() {
        x = fib(n-1);
      });
      y = fib(n-2);
    }); 
    return (x + y);
  }
}

int main (int argc, char ** argv) {
  hclib::launch([&]() {
    if (argc < 2) { return 1; }
    uint64_t n = strtoul(argv[1], NULL, 0);
    long start = get_usecs();
    uint64_t result = fib(n);
    long end = get_usecs();
    double dur = ((double)(end-start))/1000000;
    printf("Fibonacci of %" PRIu64 " is %" PRIu64 ". Time = %0.2f\n", n, result,dur);
  });
  return 0;
}

