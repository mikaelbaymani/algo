#include<queue>
#include<tuple>
#include<limits>
#include<vector>
#include<iostream>
using namespace std;

class Iterator{

  class PriorityQueue{
    class Compare{
    public:
      bool operator()(pair<int,int> p1, pair<int,int> p2) { return get<0>(p1) > get<0>(p2); }
    };
    typedef priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> PQ;
    PQ minHeap;
  public:
    void push(int value, int index) { minHeap.push(pair<int,int>(value, index)); }
    pair<int,int> peek() { return minHeap.top(); }
    void pop() { return minHeap.pop(); }
    bool empty() { return minHeap.size() == 0; }
  };

public:

  Iterator(int K, vector<vector<int>>& kLists) : K(K), kLists(kLists) {
    indeces.resize(K, 0);

    for (int k=0; k<K; ++k) {
      if (kLists[k].empty())
        continue;
      pq.push(kLists[k][0], k);
    }
  }

  int next() {
    if (pq.empty())
      return numeric_limits<int>::max();

    int value = get<0>(pq.peek());
    int index = get<1>(pq.peek());
    pq.pop();

    indeces[index]++;
    if (indeces[index] != int(kLists[index].size())) {
      pq.push(kLists[index][indeces[index]], index);
    }

    return value;
  }

private:

  int K;
  vector<int> indeces;
  vector<vector<int>>& kLists;
  PriorityQueue pq;

};


int main(int argc, char* argv[]) {

  vector<vector<int>> kLists;

  kLists.push_back(vector<int>{1,2,3,4,5,6,7,8,9});
  kLists.push_back(vector<int>{2,2,3,4});
  kLists.push_back(vector<int>{5,5,5,10,11});

  Iterator it(3, kLists);

  for (int i = 0; i < 20; ++i) {
    cout << it.next() << endl;
  }

  return 0;
}
