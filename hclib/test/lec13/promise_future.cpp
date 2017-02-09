#include "hclib_cpp.h"
#include <unistd.h>

int main(int argc, char **argv) {
  hclib::launch([&]() {
    hclib::promise_t<int> *promise_obj = new hclib::promise_t<int>();
    hclib::async([=]() {
      printf("Worker id %d is working here\n",hclib::current_worker());
      sleep(1);
      promise_obj->put(101);
    });
    printf("Worker id %d is working here\n",hclib::current_worker());
    int value = promise_obj->get_future()->get();
    printf("Result obtained = %d\n",value);
    delete(promise_obj);
  });
  return 0;
}
