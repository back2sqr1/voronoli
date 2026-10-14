#include "ConsoleColor.hpp"
#include "Point.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

Point farthest_point(Point a, std::vector<Point> points);
Point closest_point(Point a, std::vector<Point> points);
std::vector<Point> generate_points(int n, int width, int height);
std::unordered_map<Point, std::string>
map_points_to_color(std::vector<Point> points);

int main() {
  Console c;
  int n = 5;

  std::vector<Point> points = generate_points(n, c.getWidth(), c.getHeight());
  std::unordered_map<Point, std::string> color_map =
      map_points_to_color(points);

  for (int i = 0; i < c.getHeight(); i++) {
    for (int j = 0; j < c.getWidth(); j++) {
      Point cur(j, i);
      Point f_point = closest_point(cur, points);
      c.color(i, j, color_map[f_point]);
    }
  }

  for (int i = 0; i < n; i++) {
    int x = points[i].x;
    int y = points[i].y;
    c.paint(y, x, std::to_string(i), color_map[points[i]]);
  }

  c.render();

  return 0;
}

std::string set_color(int r, int g, int b) {
  std::string color = "\033[38;2;";
  color += std::to_string(r) + ";";
  color += std::to_string(g) + ";";
  color += std::to_string(b) + "m";
  return color;
}

std::unordered_map<Point, std::string>
map_points_to_color(std::vector<Point> points) {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::vector<std::string> colors = {
      set_color(239, 71, 111),  set_color(255, 209, 102),
      set_color(6, 214, 160),   set_color(17, 138, 178),
      set_color(7, 59, 76),     set_color(155, 93, 229),
      set_color(255, 107, 107), set_color(67, 170, 139),
      set_color(255, 159, 28),  set_color(58, 134, 255),
  };
  std::shuffle(colors.begin(), colors.end(), gen);

  std::unordered_map<Point, std::string> color_map;

  for (size_t i = 0; i < points.size(); i++) {
    color_map[points[i]] = colors[i % colors.size()];
  }

  return color_map;
}

Point farthest_point(Point a, std::vector<Point> points) {
  if (points.empty()) {
    throw std::invalid_argument("farthest_point requires at least one point");
  }

  double dist = a.dist(points[0]);
  Point p = points[0];
  for (size_t i = 1; i < points.size(); i++) {
    double candidate_dist = a.dist(points[i]);
    if (candidate_dist > dist) {
      dist = candidate_dist;
      p = points[i];
    }
  }
  return p;
}

Point closest_point(Point a, std::vector<Point> points) {
  if (points.empty()) {
    throw std::invalid_argument("closest_point requires at least one point");
  }

  double dist = a.dist(points[0]);
  Point p = points[0];
  for (size_t i = 1; i < points.size(); i++) {
    double candidate_dist = a.dist(points[i]);
    if (candidate_dist < dist) {
      dist = candidate_dist;
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
    bool duplicate;

    do {
      duplicate = false;
      a = Point(x(gen), y(gen));

      for (const Point &p : points) {
        if (p == a) {
          duplicate = true;
          break;
        }
      }
    } while (duplicate);

    points.emplace_back(a);
  }

  return points;
}
