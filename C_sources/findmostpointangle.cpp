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

const double FOV = 10.;
const double PI = 3.14159265;
const int NO_OF_POINTS = 1000000;

class Point{
public:
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
};

class Timer {
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
  double pivot = v[first];
  int i = first + 1;
  for (int j = first + 1; j < end; ++j) {
    if (v[j] < pivot) {
      iter_swap(v.begin()+j, v.begin()+i);
      ++i;
    }
  }
  iter_swap(v.begin()+first, v.begin()+i-1);
  return i-1;
}

void QuickSort(vector<double>& v, int end, int first=0) {
  if (first < end) {
    int q = Partition(v, first, end);
    QuickSort(v, q, first);
    QuickSort(v, end, q+1);
  }
}

int BinarySearch(const vector<double>& v,
                 double target,
                 int last,
                 int first = 0) {
  if (first <= last && v[0] < target) {
    int mid = (last - first) / 2 + first;

    if (v[last] <= target)
      return last;

    if (v[mid + 1] <= target)
      return BinarySearch(v, target, last, mid + 1);

    else
      return BinarySearch(v, target, mid, first);
  }

  return -1;
}

tuple<double,int> FindMostPointAngle(
  const vector<Point> points,
  const Point cam_center,
  double fov) {

  if (fov >= 360.) return make_tuple(.0, points.size() );

  vector<double> angles;
  angles.reserve(points.size() );

  // O(n)
  for (auto& p : points) {
    double a = atan2(p.y - cam_center.y, p.x - cam_center.x) * 180/PI;
    if (a < 0) a += 360.;
    angles.push_back( a );
  }

  // O (n log n)
  QuickSort(angles, angles.size());

  int upper, no_of_points, max_points = -1;
  double angle_at_max = .0;
  // O(n log n)
  for (unsigned index = 0; index < angles.size(); ++index) {
    if (fov + angles[index] <= 360.) {
      upper = BinarySearch(angles, fov + angles[index], angles.size() - 1);
      no_of_points = upper - index + 1;
    }

    else {
      upper = BinarySearch(angles, fov + (angles[index] - 360.), angles.size() - 1);
      no_of_points = upper + angles.size() - index + 1;
    }

    if (no_of_points > max_points) {
      max_points = no_of_points;
      angle_at_max = angles[index];
    }
  }

  angle_at_max += .5*fov;
  while(angle_at_max > 360.) { // O(1)
    angle_at_max -= 360.;
  }

  return make_tuple(angle_at_max, max_points);
}

int main(int argc, char* argv[]) {

  vector<Point> points;
  points.reserve(NO_OF_POINTS);

  {
    random_device rseed;
    mt19937 rng(rseed());
    uniform_real_distribution<> dis(-1.0, 1.0);

    for (int p = 0; p < NO_OF_POINTS; ++p)
      points.push_back(Point(dis(rng), dis(rng)));
  }

  Timer tmr;
  auto [angle, _] = FindMostPointAngle(points, Point(0, 0), FOV);
  cout << "took " << tmr.elapsed() << " seconds\n";

  cout << "fov: " << FOV << endl;
  cout << "Angle: " << angle << " [" << (angle - .5*FOV) << "," << (angle + .5*FOV);
  if (angle + .5*FOV < 360.)
    cout << "]\n";
  else
    cout << "(" << angle + .5*FOV - 360. << ")]\n";
  cout << _ << endl;
  return 0;
}
