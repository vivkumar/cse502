#include<omp.h>
#include<stdio.h>
#define SIZE 100000
int array[SIZE];

int main(int argc, char **argv) {
  int i;
  for(i=0; i<SIZE; i++) array[i] = 1;

  int sum = 0;
  #pragma omp parallel for default(shared) private(i) reduction(+:sum)
  for(i=0; i<SIZE; i++) {
    sum += array[i];
  }

  printf("Total = %d\n",sum);
  return 0;
}
