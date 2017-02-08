#include "hclib_cpp.h"
#include <unistd.h>

int main(int argc, char **argv) {
  hclib::launch([&]() {
    hclib::future_t<void> *a = hclib::async_future([=]() {
      sleep(1);
      printf("A\n");
      return;
    });
    hclib::future_t<void> *b = hclib::async_future([=]() {
      a->wait();
      printf("B\n");
      return;
    });
    hclib::future_t<void> *c = hclib::async_future([=]() {
      a->wait();
      printf("C\n");
      return;
    });
    hclib::future_t<void> *d = hclib::async_future([=]() {
      sleep(1);
      b->wait();
      c->wait();
      printf("D\n");
      return;
    });
    hclib::future_t<void> *e = hclib::async_future([=]() {
      c->wait();
      printf("E\n");
      return;
    });
    hclib::future_t<void> *f = hclib::async_future([=]() {
      d->wait();
      e->wait();
      printf("F\n");
      return;
    });
    f->wait();
    printf("Terminating\n");
  });
  return 0;
}
