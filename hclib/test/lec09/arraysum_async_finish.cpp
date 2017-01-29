#include "hclib_cpp.h"
#include <sys/time.h>

#define SIZE 480000000

double *array;
double *sum_partial;

long get_usecs (void)
{
   struct timeval t;
   gettimeofday(&t,NULL);
   return t.tv_sec*1000000+t.tv_usec;
}

void initialize() {
  array = new double[SIZE];
  for(int i=0; i<SIZE; i++) array[i] = (i+1)*0.1;
}

int main(int argc, char **argv) {

  hclib::launch([&]() {
  initialize();
  
  sum_partial = new double [hclib::num_workers()];
  for(uint64_t i =0; i<hclib::num_workers(); i++) sum_partial[i] = 0;

  assert(SIZE%hclib::num_workers() == 0);
  int chunkSize = SIZE / hclib::num_workers();

  long start = get_usecs();
  hclib::finish([&]() {
  for(int worker=0; worker<hclib::num_workers(); worker++) {
    hclib::async([=]() {
      const uint64_t start = worker * chunkSize;
      const uint64_t end = start+chunkSize;
      for(uint64_t i=start; i<end; i++) {
        sum_partial[worker] += 1/array[i];
      }
    });
  }
  });
  
  double sum = 0;
  for(int i=0; i<hclib::num_workers(); i++) sum += sum_partial[i];
  long end = get_usecs();
  double dur = ((double)(end-start))/1000000;
  printf("Sum = %.3f\n", sum);
  printf("Time = %f\n",dur);

  delete (array);
  delete(sum_partial);
  });

  return 0;
}
