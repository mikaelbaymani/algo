#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
// Find the contiguous subarray within
// an array (containing at least one number)
// which has the largest sum.
int CSA(vector<int> array) {
  vector<int> V(array.size());
  V[0] = array[0];
  for(int i=1; i<array.size(); ++i) {
    V[i] = max(V[i-1]+array[i], array[i]);
  }
  return *max_element(V.begin(), V.end());
}

int main() {
  vector<int> array{-2,1,-3,4,-1,2,1,-5,4};
  cout << CSA(array) << "\n";
  return 0;
}
