#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

template <typename W, typename L>
class PriorityQueue{
  class Compare{
  public:
    bool operator()(pair<W,L> p1, pair<W,L> p2) {
#if 0
      int diff1 = p1.first - p1.second;
      int diff2 = p2.first - p2.second;
      if (diff1 > diff2) return false;
      else if (diff1 < diff2) return true;
      else if (p1.first > p2.first) return false;
      return true;
#else
      double ratio1 = (double)p1.first / p1.second;
      double ratio2 = (double)p2.first / p2.second;
      return ratio2 > ratio1;
#endif
    }
  };
  typedef priority_queue<pair<W,L>, vector<pair<W,L> >, Compare> PQ;
  PQ maxHeap;

public:
  void insert(W weight, L length){
    maxHeap.push(pair<W,L>(weight, length));
  }

  pair<W,L> top(){
    pair<W,L> p = maxHeap.top();
    maxHeap.pop();
    return p;
  }

  bool isEmpty(){
    return maxHeap.size()==0;
  }
};

class Tuple{
public:
    int first, second;
    Tuple(): first(0), second(0) { }
    friend istream& operator>>(istream& i, Tuple& t) { return i >> t.first >> t.second;}
};

int main(int argc, char* argv[])
{
  int64_t C=0, sum=0;
  int weight,length;
  pair<int, int> p;
  PriorityQueue<int,int> PQ;

  ifstream datafile("jobs.txt");
  if (datafile.good()) {
    string first_line;
    getline(datafile, first_line);

    int no_of_tuples = stoi(first_line);
    cout << "# of jobs: " << no_of_tuples << endl;

    istream_iterator<Tuple> start(datafile), end;
    vector<Tuple> data(start, end);
    for(auto& tuple : data) {
      // cout << tuple.first << ", " << tuple.second << endl;
      PQ.insert(tuple.first, tuple.second);
    }
  }

  while(!PQ.isEmpty()){
    p = PQ.top();

    weight=p.first;
    length=p.second;

    C = C + length;
    //cout << weight << " * " << C << endl;
    sum = sum + weight*C;
  }

  cout << sum << "\n";
  return 0;
}
