#include "hclib_cpp.h"
#include <unistd.h>

int main(int argc, char **argv) {
  hclib::launch([&]() {
    hclib::future_t<int> *f = hclib::async_future([=]() {
      printf("Worker id %d is working here\n",hclib::current_worker());
      sleep(1); 
      return 101;
    });
    printf("Worker id %d is working here\n",hclib::current_worker());
    int value = f->get();
    printf("Result obtained = %d\n",value);
  });
  return 0;
}
