#include <cmath>
class Point {
public:
  Point(double x, double y) {
    this->x = x;
    this->y = y;
  }

  double dist(Point a) {
    double dx = a.x - x;
    double dy = a.y - y;
    return std::sqrt((dx * dx) + (dy * dy));
  }

  double x;
  double y;
};
