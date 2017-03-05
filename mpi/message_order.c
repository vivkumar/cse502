/*
 * Author: Vivek Kumar (vivekk@iiitd.ac.in)
 */

/*
 * Example to show that if a sender sends two messages (Msg_1 and Msg_2) in succession 
 * to same destination, and both match the same receive, the recv operation will 
 * always receive Msg_1 before Msg_2
 */

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX 10

int main(int argc, char **argv) {
  int i;
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 1) {
    for(i=0; i<MAX; i++) {
      MPI_Send(&i, 1, MPI_INT, 0, 123, MPI_COMM_WORLD); 
    }
  }
  else if(rank == 0) {
    int buf[MAX];
    MPI_Status stats;
    for(i=0; i<MAX; i++) {
      MPI_Recv(&buf[i], 1, MPI_INT, 1, 123, MPI_COMM_WORLD, &stats); 
      assert(buf[i] == i); // This will never fail!
    }
    printf("0: Test SUCCESS\n");
  }

  MPI_Finalize();
  return 0;
}
