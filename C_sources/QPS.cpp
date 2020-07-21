#include <chrono>
#include <unistd.h>
#include <iostream>
using namespace std;

class Timer {
public:
  Timer() : beg_(clock_::now()) { }
  virtual ~Timer() { }

  virtual void reset() {
    beg_ = clock_::now();
  }

  virtual double elapsed() const {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
  }

private:
  typedef std::chrono::high_resolution_clock clock_;
  typedef std::chrono::duration<double, std::ratio<1> > second_;
  std::chrono::time_point<clock_> beg_;
};

class MockTimer : public Timer {
public:
  MockTimer() : elapsed_(.0) { }

  void reset() {
    elapsed_ = .0;
  }

  double elapsed() const {
    return elapsed_;
  }

  void fakeSleep(double d) {
    elapsed_ = d;
  }

private:
  double elapsed_;
};

class QPS {
  Timer* tmr;
  int allowedQPS;
  int counterQPS;
public:
  QPS() : tmr(new Timer) {}
  QPS(Timer* tmr) : tmr(tmr) { }
  ~QPS() { delete tmr; }

  void setAllowableQPS(int capacityQPS) {
    allowedQPS = capacityQPS;
    counterQPS = capacityQPS;
  }

  bool call() {
    bool isAllowed = false;
    if (tmr->elapsed() > 1.) {
      counterQPS = allowedQPS;
      tmr->reset();
    }
    if (counterQPS > 0) {
      counterQPS--;
      isAllowed = true;
    }

    return isAllowed;
  }
};

int main(int argc, char* argv[]) {
  MockTimer* mock = new MockTimer;
  QPS server(mock);

  server.setAllowableQPS(2);
  cout << ( server.call()? "true": "false" ) << endl;
  cout << ( server.call()? "true": "false" ) << endl;
  cout << ( server.call()? "true": "false" ) << endl;
  mock->fakeSleep(1000);
  cout << ( server.call()? "true": "false" ) << endl;

  return 0;
}
