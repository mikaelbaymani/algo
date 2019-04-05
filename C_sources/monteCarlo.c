#include <time.h>
#include <stdio.h>
#include <stdlib.h>
const unsigned int Ntotal = 1000000000;
inline static double Random() { return (double)rand()/(double)RAND_MAX; }

/** gcc -o monteCarlo monteCarlo.c */
void main() {
  srand(time(NULL));
  double X,Y,D,PI;
  unsigned int Ninner = 0;

  for(unsigned int n = 0; n < Ntotal; n++) {
    X = Random(), Y = Random();

    D = X*X + Y*Y;
    if (D <= 1.) {
      ++Ninner;
    }
  }

  PI = (double)(4*Ninner) / (double)Ntotal;

  printf("PI: %f \n", PI);
}
