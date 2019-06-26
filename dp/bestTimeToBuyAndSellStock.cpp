#include<iostream>
#include<vector>
using namespace std;
// Say you have an array for which the
// i.th element is the price of a given
// stock on day i.

// If you were only permitted to complete
// at most one transaction (ie. buy one and
// sell one share of the stock), design an
// algorithm to find the maximum profit.

int buyAndSell(int n, vector<int>& Prices) {
  vector<int> R(n);
  R[0] = 0;
  int Min_value = Prices[0];
  for(int i=1; i < n; ++i) {
    Min_value = min(Min_value, Prices[i]);
    R[i] = max(R[i-1], Prices[i] - Min_value);
  }
  return R[n-1];
}

int main(int argc, char** argv) {
  vector<int> Prices1 = {7,1,5,4,6,4},
              Prices2 = {7,6,4,3,1};
  cout << buyAndSell(6, Prices1) << endl << buyAndSell(5, Prices2) << "\n";
  return 0;
}
