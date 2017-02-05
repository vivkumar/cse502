#include "hclib_cpp.h"

/*
 * Example to show the usage of global isolation
 */
using namespace std;
#define LIMIT 10000

int main (int argc, char ** argv) {
  hclib::launch([&]() {
    int *ptr = new int;
    *ptr = 0;

    hclib::loop_domain_t loop = {0, LIMIT, 1, 1};
    hclib::finish([&]() {
      hclib::forasync1D(&loop,[=](int i) {
        hclib::isolated([=]() {  //global isolation
           *ptr += 1;
        });
      }, FORASYNC_MODE_RECURSIVE);
    });
 
    printf("Result=%d\n",*ptr);
    assert(*ptr==LIMIT && "Test Failed");
    printf("Test Passed\n");
    delete(ptr);
  });
  return 0;
}

