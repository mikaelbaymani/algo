#include<iostream>
using namespace std;
// You want to climb n steps. At any step,
// you can either climb 1, 2 or 3 steps.
// How many different ways can you climb
// the n stairs?
int main(int argc, char** argv) {
  int n = 10;
  int* S = new int[n+1];
  S[1] = 1;
  S[2] = 2;
  S[3] = 4;
  for(int i=4; i<=n; ++i) {
    S[i] = S[i-1] + S[i-2] + S[i-3];
  }
  cout << S[n] << endl;
  delete [] S;
  return 0;
}
