#include <omp.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int a=1, b=2;
  #pragma omp parallel default(none) firstprivate(a,b)
  #pragma omp single 
  {
    int c=3;
    #pragma omp task 
    {
      printf("IN: a=%d,b=%d,c=%d\n",a++,b++,c++);
    }
    #pragma taskwait
    printf("OUT: c=%d\n",c);
  }
  printf("IN: a=%d,b=%d\n",a,b);

  return 0;
}
