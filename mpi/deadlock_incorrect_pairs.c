/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show that if blocking send and receive (MPI_Send and MPI_Recv)
 * is incorrectly paired then it will lead to deadlock
 */

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
  int rank, np;
  MPI_Status stats;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  int tag = 1;
  int buf;

  /*
   * Interchange the order of send/recv in one rank to break the deadlock
   */
  if(rank == 0) {
    MPI_Recv(&buf, 1, MPI_INT, 1, tag, MPI_COMM_WORLD, &stats);
    MPI_Send(&rank, 1, MPI_INT, 1, tag, MPI_COMM_WORLD); 
  }
  else if (rank == 1) {  
    MPI_Recv(&buf, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &stats);
    MPI_Send(&rank, 1, MPI_INT, 0, tag, MPI_COMM_WORLD); 
  }

  MPI_Finalize();
  return 0;
}
