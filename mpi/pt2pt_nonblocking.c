/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show that proper usage of non-blocking point-to-point
 * communication in MPI by using the parallel array sum example
 */

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

#define TOTAL_AT_RANK 1024

int main(int argc, char **argv) {
  int i, my_sum, total_sum;
  int rank, np;
  MPI_Request *req_array;
  MPI_Status *stats_array;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  printf("procs = %d and rank = %d\n",np, rank);

  // Allocate request and status array
  req_array = (MPI_Request*) malloc(sizeof(MPI_Request) * (np-1));  
  stats_array = (MPI_Status*) malloc(sizeof(MPI_Status) * (np-1));  

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

  // We need an array of total_sum as each rank will send
  // their result in a non-blocking API
  int* partial_sum = (int*) malloc(sizeof(int) * np);

  int tag = 123; // any value
  // each non-root process will now send the partial sum
  // to the root process
  if(rank > 0) {
    int dest = 0;
    MPI_Status stats;
    // Fire a non-blocking send
    MPI_Isend(&my_sum, 1, MPI_INT, dest, tag, MPI_COMM_WORLD, &(req_array[rank-1])); 
    // Here you can do some useful computation in parallel to the non-blocking send
    // Now wait for the send to complete
    MPI_Wait(&(req_array[rank-1]), &stats);
  }
  else {
    // first root will add its own partial sum
    partial_sum[0] = my_sum;
    for(i=1; i<np; i++) {
      int src = i;
      // Fire a non-blocking receive
      MPI_Irecv(&partial_sum[src], 1, MPI_INT, src, tag, MPI_COMM_WORLD, &(req_array[src-1]));
    }
    // Here you can do some useful computation in parallel to the non-blocking receive
    // Now wait for ALL the non-blocking receive to complete
    MPI_Waitall(np-1, req_array, stats_array);
  }

  //Verify the result at root
  if(rank == 0) {
    int expected = 0; 
    total_sum=0;
    for(i=0; i<np * TOTAL_AT_RANK; i++) expected += i;
    for(i=0; i<np; i++) total_sum += partial_sum[i]; 
    if(total_sum == expected) printf("0: Test SUCCESS\n");
    else printf("0: Test FAILED\n");
  }

  free(array);
  free(partial_sum);
  free(req_array);
  free(stats_array); 

  MPI_Finalize();
  return 0;
}

