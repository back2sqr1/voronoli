#include <cmath>
#include <functional>
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

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }

  double x;
  double y;
};

namespace std {
template <> struct hash<Point> {
  std::size_t operator()(const Point &p) const {
    std::size_t h1 = std::hash<int>{}(p.x);
    std::size_t h2 = std::hash<int>{}(p.y);

    return h1 ^ (h2 << 1);
  }
};
} // namespace std
