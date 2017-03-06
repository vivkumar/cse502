/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show hybrid parallel programming using OpenMP and MPI
 */

#include<mpi.h>
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define TOTAL_AT_RANK 1024

int main(int argc, char **argv) {
  int i, my_sum, total_sum;
  int rank, np;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  printf("procs = %d and rank = %d\n",np, rank);

  // malloc the input array that will be equally 
  // divided into total processes
  int* array = (int*) malloc(sizeof(int) * np * TOTAL_AT_RANK);

  /*
   * Initialize the array. In real world
   * applications this array could be read by
   * each process from an input file in parallel.
   */
  int start_index = TOTAL_AT_RANK * rank;
  int end_index = start_index + TOTAL_AT_RANK;
  for(i=start_index; i<end_index; i++) {
    array[i] = i;
  }

  // Each process will now compute the local sum
  // Note: we are running this computation outside the 
  // the above for-loop just to mimic an actual 
  // computation.
  my_sum = 0;

  #pragma omp parallel for default(shared) private(i) reduction(+:my_sum)
  for(i=start_index; i<end_index; i++) my_sum += array[i];

  MPI_Reduce(&my_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  //Verify the result at root
  if(rank == 0) {
    int expected = 0; 
    for(i=0; i<np * TOTAL_AT_RANK; i++) expected += i;
    if(total_sum == expected) printf("0: Test SUCCESS\n");
    else printf("0: Test FAILED\n");
  }

  free(array);
  MPI_Finalize();
  return 0;
}
