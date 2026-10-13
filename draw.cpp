#include "ConsoleColor.hpp"
#include "Point.hpp"
#include <random>
#include <vector>

Point farthest_point(Point a, std::vector<Point> points);
std::vector<Point> generate_points(int n, int width, int height);

int main() {
  Console c;
  int n = 5;

  std::vector<Point> points = generate_points(n, c.getWidth(), c.getHeight());
  for (int i = 0; i < n; i++) {
    int x = points[i].x;
    int y = points[i].y;
    c.paint(y, x, std::to_string(i));
  }
  c.render();
  return 0;
}

Point farthest_point(Point a, std::vector<Point> points) {
  double dist = 0;
  Point p = points[0];
  for (int i = 0; i < points.size(); i++) {
    if (a.dist(points[i]) > dist) {
      dist = a.dist(points[i]);
      p = points[i];
    }
  }
  return p;
}

std::vector<Point> generate_points(int n, int width, int height) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> x(0, width - 1);
  std::uniform_int_distribution<int> y(0, height - 1);
  std::vector<Point> points;
  for (int i = 0; i < n; i++) {
    Point a(x(gen), y(gen));
    points.emplace_back(a);
  }
  return points;
}
