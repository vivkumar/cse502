/*
 * Ported from HJlib for CSE 502 course at IIITD
 * Author: Vivek Kumar
 */

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>

double **a, **b, **c;

/*
 * Timer routine
 */
long get_usecs (void) {
   struct timeval t;
   gettimeofday(&t,NULL);
   return t.tv_sec*1000000+t.tv_usec;
}

/*
 * Intialize input matrices and the output matrix
 */
void init(int n) {
  a = new double*[n];
  b = new double*[n];
  c = new double*[n];
  for(int i=0; i<n; i++) {
    a[i] = new double[n];
    b[i] = new double[n];
    c[i] = new double[n];
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      a[i][j] = 1.0;  
      b[i][j] = 1.0;  
      c[i][j] = 0;
    }    
  }
}

/*
 * release memory
 */
void freeall(int n) {
  for(int i=0; i<n; i++) {
    delete(a[i]);
    delete(b[i]);
    delete(c[i]);
  }
  delete (a);
  delete (b);
  delete (c);
}

/*
 * Validate the result of matrix multiplication
 */
int verify(int n) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(c[i][j] != n) {
        printf("result = %.3f\n",c[i][j]);
        return false;
      }
    }
  }
  return true;
}

void multiply(int n) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      for(int k=0; k<n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }    
  }
}

int main(int argc, char** argv) {
  int n = argc>1 ? atoi(argv[1]) : 1024;
  // initialize
  init(n);
  //start timer
  long start = get_usecs();
  //multiply matrices
  multiply(n);
  //end timer
  long end = get_usecs();
  double dur = ((double)(end-start))/1000000;
  //validate result
  int result = verify(n);
  printf("MatrixMultiplication result = %d, Time = %.3f\n",result, dur);
  //release memory
  freeall(n);
  return 0;
}
