/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show that proper usage of blocking point-to-point
 * communication in MPI by using the parallel array sum example
 */

#include<mpi.h>
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
  for(i=start_index; i<end_index; i++) my_sum += array[i];

  int tag = 123; // any value
  MPI_Status stats;
  // each non-root process will now send the partial sum
  // to the root process
  if(rank > 0) {
    int dest = 0;
    MPI_Send(&my_sum, 1, MPI_INT, dest, tag, MPI_COMM_WORLD); 
  }
  else {
    // first root will add its own partial sum
    total_sum = my_sum;
    for(i=1; i<np; i++) {
      int src = i;
      int recv_sum;
      MPI_Recv(&recv_sum, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &stats);
      total_sum += recv_sum; 
    }
  }

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
