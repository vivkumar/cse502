#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>

uint64_t fib(uint64_t n) {
  if (n < 2) { 
    return n; 
  } else {
    uint64_t x = fib(n-1);
    uint64_t y = fib(n-2);  
    return (x + y);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) { return 1; }
  uint64_t n = strtoul(argv[1], NULL, 0);
  uint64_t result = fib(n);
  printf("Fibonacci of %" PRIu64 " is %" PRIu64 ".\n", n, result);
  return 0; 
}
