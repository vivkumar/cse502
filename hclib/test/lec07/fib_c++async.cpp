#include <iostream>
#include <future>
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
  if (n < 18) { 
    return fib_seq(n);
  } else {
    /*
    std::future<uint64_t> f1 = std::async(std::launch::async, [=]() {
				 fib(n-1);
                               });
    */
    std::future<uint64_t> f1 = std::async(std::launch::async, fib, n-1);
    uint64_t y = fib(n-2);
    uint64_t x = f1.get();
    return x + y;
  }
}

int main(int argc, char **argv) {
  if (argc < 2) { return 1; }
  uint64_t n = strtoul(argv[1], NULL, 0);
  long start = get_usecs();
  uint64_t result = fib(n);
  long end = get_usecs();
  double dur = ((double)(end-start))/1000000;
  printf("Fibonacci of %" PRIu64 " is %" PRIu64 ". Time = %.3f sec\n", n, result, dur);
  return 0; 
}
