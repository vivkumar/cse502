#include <iostream>
#ifdef PARALLEL
#include "hclib_cpp.h"
#endif
#include <sys/time.h>

#define SIZE (100*1048576)
#define THRESHOLD (4*1024)
int array[SIZE];

long get_usecs (void)
{
   struct timeval t;
   gettimeofday(&t,NULL);
   return t.tv_sec*1000000+t.tv_usec;
}

int sum(int low, int high) {
  if((high-low) > THRESHOLD) {
    int x, y;
    int mid = (low+high)/2;
#ifdef PARALLEL
    HCLIB_FINISH {
        hclib::async([&]() {
          x = sum(low, mid);
        });
        y = sum(mid, high);
    }
#else
    x = sum(low, mid);
    y = sum(mid, high);
#endif
    return x+y;
  } else {
    int x=0;
    for(int i=low; i<high; i++) x+= array[i];
    return x;
  }
}

int main (int argc, char ** argv) {
#ifdef PARALLEL
  hclib::launch([&]() {
#endif
    std::fill(array, array+SIZE, 1);
    long start = get_usecs();
    int result = sum(0, SIZE);
    long end = get_usecs();
    double dur = ((double)(end-start))/1000000;
    if(result == SIZE) std::cout<<"Test passed in "<< dur << " seconds" << std::endl;
    else std::cout<<"Test failed";
#ifdef PARALLEL
  });
#endif
  return 0;
}

