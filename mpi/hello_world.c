/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

/*
 * The first and the simplest hello world MPI Program 
 */

int main(int argc, char **argv) {
  int rank, np;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  printf("Hello World from Rank %d. There are total %d MPI processes\n",rank, np);

  MPI_Finalize();
  return 0;
}
