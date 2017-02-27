#include<omp.h>
#include<stdio.h>

void foo() {
  int i;
  printf("Before of the parallel for\n");
  #pragma omp for
  for(i=0; i<5;i++) {
    printf("I am worker-%d\n",omp_get_thread_num());
  }
}

int main(int argc, char **argv) {
    
  foo();
  #pragma omp parallel
  foo();

  return 0;
}
