#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Triplet{
public:
  int press;
  int cost;
  int dev;
  Triplet() { }
  Triplet(int p, int c, int d) :
   press(p), cost(c), dev(d) {
  }
};

class PriorityQueue{
private:
  class Cmp{
  public:
    bool operator()(
      Triplet t1,
      Triplet t2) {
        if (t1.cost > t2.cost)
          return true;
        else if (t1.cost < t2.cost)
          return false;
        else
          return t1.dev > t2.dev;
      }
  };
  
  typedef priority_queue<Triplet, vector<Triplet>, Cmp> PQ;
  PQ minHeap;
public:
  void push(int p, int c, int d) {
     minHeap.push(Triplet(p,c,d));
  }
  
  Triplet peek() {
    return minHeap.top();
  }
  
  void pop() {
    minHeap.pop();
  }
  
  bool empty() {
    return minHeap.size() == 0;
  }
};

int calc_cost(int value) {
  int cost = 0;
  int rem = -1;
  
  do {
    int curr = value % 10;
    if (rem < 0 || rem == curr) {
      cost += 1;
    }
    else {
      cost += 2;
      cost += 1;
    }
    rem = curr;
  } while(value/=10);
  
  return cost;
}

vector<int> gen_cases(int min, int sec) {
  vector<int> vec;
  vec.push_back(min*100 + sec);
  if (min > 0 && sec <= 39) {
    vec.push_back((min-1)*100 + 60+sec);
  }
  return vec;
}

int calc_dev(int target, int pivot) {
  int min = target/100;
  int sec = target%100;
  int tot = min*60 + sec;
  return abs(pivot - tot);
}

int best_press(int min, int sec) {
  set<int> s;
  PriorityQueue PQ;
  int result = -1;
  int tot_sec = min*60 + sec;
  int max_sec = tot_sec*1.1;
  int min_sec = tot_sec*0.9;
  cout << "tot: "<< tot_sec << 
          ", min: " << min_sec
       << ", max: " << max_sec
       << "\n";
  
  for(int i=min_sec;i<=max_sec;++i) {
    for(auto& c:gen_cases(i/60,i%60))
      s.insert(c);
  }
  for(auto& item: s) {
    int cost = calc_cost(item);
    int dev = calc_dev(item,tot_sec);
    PQ.push(item, cost, dev);
  }
  cout << "press\tcost\tdev\n";
  while (!PQ.empty()) {
    Triplet t;
    t = PQ.peek();
    cout << t.press << "\t"
         << t.cost << "\t"
         << t.dev << "\n";
    if (result < 0) {
      result = t.press;
    }
    PQ.pop();
  }
  
  return result;
}

int main(int argc, char* argv[]) {
  int result = best_press(2,00);
  cout << "best press:\t" << result;
  return 0;
}