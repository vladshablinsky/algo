#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kCnt = 3;

struct Point {
  int x, y;
};

int main() {
  vector<Point> points(kCnt);
  for (int i = 0; i < kCnt; ++i) {
    scanf("%d%d", &points[i].x, &points[i].y);
  }

  sort(points.begin(), points.end(), [](auto& e1, auto& e2) { return e1.x < e2.x; });
  vector<pair<Point, Point>> out;
  auto [min_y, max_y] = std::minmax_element(points.begin(), points.end(),
      [](auto& e1, auto& e2) { return e1.y < e2.y; });

  out.emplace_back(points[0], Point{points[1].x, points[0].y});
  out.emplace_back(Point{points[1].x, min_y->y}, Point{points[1].x, max_y->y});
  out.emplace_back(points[2], Point{points[1].x, points[2].y});

  printf("%d\n", out.size());
  for (auto& [from, to]: out) {
    printf("%d %d %d %d\n", from.x, from.y, to.x, to.y);
  }
}
