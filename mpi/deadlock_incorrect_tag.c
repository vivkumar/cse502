/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show that incorrect tags in MPI_Send and MPI_Recv
 * will lead to deadlock 
 */

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
  int i, rank, np;
  MPI_Status stats;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  if(rank > 0) {
    int dest = 0;
    // Note: the tag being used here is not same as that in MPI_Recv
    int tag = rank;
    MPI_Send(&rank, 1, MPI_INT, dest, tag, MPI_COMM_WORLD); 
  }
  else {
    for(i=1; i<np; i++) {
      int buf;
      int src = i;
      // Note: the tag being used here is not same as that in MPI_Send
      // The tag should match all the tag used in MPI_Send     
      // Since the tags are different, this send-recv will deadlock
      int tag = 123;
      MPI_Recv(&buf, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &stats);
    }
  }

  MPI_Finalize();
  return 0;
}
