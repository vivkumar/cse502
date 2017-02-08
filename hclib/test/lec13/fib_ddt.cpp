#include "hclib_cpp.h"
#include <iostream>

uint64_t threshold = 18;

uint64_t fib_serial(uint64_t n) {
    if (n <= 2) return 1;
    return fib_serial(n-1) + fib_serial(n-2);
}

void fib(uint64_t n, hclib::promise_t<uint64_t> *res) {
  if (n <= threshold) {
    uint64_t r = fib_serial(n);
    res->put(r);
    return;
  } 

  // compute f1 asynchronously
  hclib::promise_t<uint64_t> * f1 = new hclib::promise_t<uint64_t>();
  hclib::async([=]() { 
    fib(n - 1, f1);
  });

  // compute f2 serially (f1 is done asynchronously).
  hclib::promise_t<uint64_t>* f2 = new hclib::promise_t<uint64_t>();
  hclib::async([=]() { 
    fib(n - 2, f2);
  });

  // wait for dependences, before updating the result
  hclib::async_await([=] {
    uint64_t r = f1->get_future()->get() + f2->get_future()->get();
    res->put(r);
    delete(f1); delete(f2);
  }, f1->get_future(), f2->get_future());
}

int main(int argc, char** argv) {
    hclib::launch([&]() {
        uint64_t n = argc == 1 ? 30 : atoi(argv[1]);
        hclib::promise_t<uint64_t> * promise = new hclib::promise_t<uint64_t>();
        hclib::finish([=] {
            fib(n, promise);
        });
        uint64_t res = promise->get_future()->get();
        delete(promise);
        std::cout << "Fib(" << n << ") = " << res << std::endl;
    });
    return 0;
}
