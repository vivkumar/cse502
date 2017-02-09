#include "hclib_cpp.h"
#include <iostream>
#include <inttypes.h>

uint64_t threshold = 18;

uint64_t fib_serial(uint64_t n) {
    if (n < 2) return n;
    return fib_serial(n-1) + fib_serial(n-2);
}

uint64_t fib(uint64_t n) {
  if (n < threshold) {
    return fib_serial(n);
  } 

  // compute f1 asynchronously
  hclib::future_t<uint64_t>* f1 = hclib::async_future([=]() { 
    uint64_t x = fib(n - 1);
    return x;
  });

  uint64_t y = fib(n - 2);
  // wait for dependences, before updating the result
  return y + f1->get();
}

int main(int argc, char** argv) {
    hclib::launch([&]() {
        int n = argc == 1 ? 40 : atoi(argv[1]);
        uint64_t res = fib(n);
        std::cout << "Fib(" << n << ") = " << res << std::endl;
    });
    return 0;
}
