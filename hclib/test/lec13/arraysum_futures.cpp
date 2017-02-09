
#include "hclib_cpp.h"
#include <sys/time.h>

#define SIZE 100000000

double array[SIZE];

long get_usecs (void)
{
   struct timeval t;
   gettimeofday(&t,NULL);
   return t.tv_sec*1000000+t.tv_usec;
}

void initialize() {
  for(int i=0; i<SIZE; i++) array[i] = (i+1)*0.1;
}

int main(int argc, char **argv) {

  hclib::launch([&]() {
  initialize();

  long start = get_usecs();

  hclib::future_t<double> *sum1 = hclib::async_future([=]() {
    printf("Execution on worker: %d\n",hclib::current_worker());
    double sum=0;
    for(int i=0; i<SIZE/2; i++) {
      sum += 1/array[i];
    }
    return sum;
  });

  hclib::future_t<double> *sum2 = hclib::async_future([=]() {
    printf("Execution on worker: %d\n",hclib::current_worker());
    double sum=0;
    for(int i=SIZE/2; i<SIZE; i++) {
      sum += 1/array[i];
    }
    return sum;
  });

  double sum = sum1->get() + sum2->get();

  long end = get_usecs();
  double dur = ((double)(end-start))/1000000;
  printf("Sum = %.3f\n",sum);
  printf("Time = %f\n",dur);

  });

  return 0;
}
