#include<iostream>
#include<vector>
using namespace std;
// You are a professional robber planning to rob houses
// along a street. Each house has a certain amount of
// money stashed, the only constraint stopping you from
// robbing each of them is that adjacent house have
// security system connected and it will automatically
// contact the police if two adjacent houses were broken
// into on the same night.

// > Given a list of non-negative integers representing
//   the amount of money of each house, determine the
//   maximum amount of money you can rob tonight without
//   alerting the police.
int rob(int n, vector<int>& nums) {
  vector<int> R(n);
  R[0] = nums[0];
  R[1] = max(nums[0], nums[1]);
  for (int i=2; i<n; ++i) {
    R[i] = max(R[i-1], nums[i] + R[i-2]);
  }
  return R[n-1];
}

int main(int argc, char** argv) {
  vector<int> money{1,2,3,4,5};
  cout << rob(5/*# of houses*/, money) << "\n";
  vector<int> money2{1,2,3,4,5,6};
  cout << rob(6/*# of houses*/, money2) << "\n";
  return 0;
}
