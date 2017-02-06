#include "hclib_cpp.h"
#include <inttypes.h>

static uint64_t result = 0;

uint64_t fib_seq(int n) {
  if (n < 2) {
    return n;
  }
  else {
    return fib_seq(n-1) + fib_seq(n-2);
  }
}

void fib(uint64_t n) {
  if (n < 18) { 
    uint64_t value = fib_seq(n);
    hclib::isolated([=]() {
      result += value;
    });
  } else {
    hclib::async([=]() {
      fib(n-1);
    });
    fib(n-2);
  }
}

int main(int argc, char **argv) {
  hclib::launch([&]() {
    if (argc < 2) { return 1; }
    uint64_t n = strtoul(argv[1], NULL, 0);
      hclib::finish([=]() {
    fib(n);
    });
    printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n", n, result);
  });
  return 0; 
}
