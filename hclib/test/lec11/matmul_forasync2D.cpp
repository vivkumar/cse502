/*
 * Ported from HJlib for CSE 502 course at IIITD
 * Author: Vivek Kumar
 */

#include "hclib_cpp.h"
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
void init(int n, int tile) {
  a = new double*[n];
  b = new double*[n];
  c = new double*[n];

  hclib::loop_domain_t loop1 = {0, n, 1, tile};

  hclib::finish([&]() {
    hclib::forasync1D(&loop1, [=](int i) {
      a[i] = new double[n];
      b[i] = new double[n];
      c[i] = new double[n];
    }, FORASYNC_MODE_RECURSIVE);
  });
  
  hclib::loop_domain_t loop2[2] = { {0, n, 1, tile}, {0, n, 1, tile} };

  hclib::finish([&]() {
    hclib::forasync2D(loop2, [=](int i, int j) {
      a[i][j] = 1.0;  
      b[i][j] = 1.0;  
      c[i][j] = 0;
    }, FORASYNC_MODE_RECURSIVE);    
  });
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

void multiply(int n, int tile) {
  hclib::loop_domain_t loop[2] = { {0, n, 1, tile}, {0, n, 1, tile} };

  hclib::finish([&]() {
    hclib::forasync2D(loop, [=](int i, int j) {
      for(int k=0; k<n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }, FORASYNC_MODE_RECURSIVE);    
  });
}

int main(int argc, char** argv) {
  hclib::launch([&]() {
  int n = argc>1 ? atoi(argv[1]) : 1024;
  int tile = argc>2 ? atoi(argv[2]) : 1;
  // initialize
  init(n, tile);
  //start timer
  long start = get_usecs();
  //multiply matrices
  multiply(n, tile);
  //end timer
  long end = get_usecs();
  double dur = ((double)(end-start))/1000000;
  //validate result
  int result = verify(n);
  printf("MatrixMultiplication result = %d, Time = %.3f\n",result, dur);
  //release memory
  freeall(n);
  });
  return 0;
}
