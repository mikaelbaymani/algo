#include <tuple>
#include <chrono>
#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include <iterator>
// Ref: From Software Engineer Interview Unleashed @ udemy.com
// ONSITE INTERVIEW EXAMPLE 2
using namespace std;

const double PI = 3.14159265;
const double EPSILON = 1e-4;
const int NO_OF_POINTS = 1000000;

struct Point {
  double x;
  double y;
  Point(double x, double y): x(x), y(y) {
  }
};

class Timer
{
public:
  Timer()
    : beg_(clock_::now()) {}

  void reset() {
    beg_ = clock_::now();
  }

  double elapsed() const {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
  }

private:
  typedef std::chrono::high_resolution_clock clock_;
  typedef std::chrono::duration<double, std::ratio<1> > second_;
  std::chrono::time_point<clock_> beg_;
};

int Partition(vector<double>& v, int first, int end) {
  int pivot = v[first];
  int i = first + 1;
  for(int j = first + 1; j < end; ++j) {
    if(v[j] < pivot) {
      iter_swap(v.begin()+j, v.begin()+i);
      ++i;
    }
  }
  iter_swap(v.begin()+first, v.begin()+i-1);
  return i-1;
}

void QuickSort(vector<double>& v, int end, int first=0) {
  if(first < end) {
    int q = Partition(v, first, end);
    QuickSort(v, q, first);
    QuickSort(v, end, q+1);
  }
}

bool AreSame(double a, double b) {
  return fabs(a - b) < EPSILON;
}

int BinarySearch(const vector<double>& vec,
                 double target,
                 int last,
                 int first = 0) {

  if(first <= last && vec[0] < target) {
    int mid = (last - first) / 2 + first;

    if(target > vec[last] || AreSame(vec[last], target)) {
      return last;
    }

    if(target > vec[mid+1] || AreSame(vec[mid+1], target)) {
      return BinarySearch(vec, target, last, mid+1);
    }
    else {
      return BinarySearch(vec, target, mid, first);
    }
  }

  return -1;
}

tuple<double, int> FindMostPointAngle(
  const vector<Point>& points,
  const Point& cam_center,
  double fov) {

  vector<double> angles;
  angles.reserve(points.size());

  for(auto& p : points) { // O(n)
    double angle = atan2(p.y-cam_center.y, p.x-cam_center.x)*180/PI;
    if (angle < 0) {
      angle += 360.0;
    }
    angles.push_back( angle );
  }

  QuickSort(angles, angles.size()); // O(n log n)

  int max_points = 0;
  double angle_at_max = 0.0;
  for(unsigned int i = 0; i < angles.size(); ++i) { // O(n log n)
    int nr_of_points = 0;
    if (fov + angles[i] < 360) {
      int index = BinarySearch(angles, fov + angles[i], angles.size()-1);
      nr_of_points = index - i + 1;
    }
    else {
      int index1 = BinarySearch(angles, 360, angles.size()-1);
      int index2 = BinarySearch(angles, fov+angles[i]-360, angles.size()-1);
      nr_of_points = index1 + index2 - i + 2;
    }

    if (nr_of_points > max_points) {
      max_points = nr_of_points;
      angle_at_max = angles[i];
    }
  }

  double result = angle_at_max + fov/2;
  while (result > 360.) { // O(1)
    result -= 360.;
  }

  return make_tuple(result, max_points);
}

int main(int argc, char* argv[]) {
  vector<Point> points;
  points.reserve(NO_OF_POINTS);
  random_device rseed;
  mt19937 rng(rseed());
  uniform_real_distribution<> dis(-1.0, 1.0);
  for(int p = 0; p < 1000000; ++p) {
    points.push_back(Point(dis(rng), dis(rng)));
  }

  Timer tmr;
  auto [angle, _] = FindMostPointAngle(points, Point(0.0,0.0), 15.0);

  cout << "took " << tmr.elapsed() << " seconds\n";
  cout << "Angle [degrees]: " << angle << "\n";
  cout << _ << "\n";
  return 0;
}
