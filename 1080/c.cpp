#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
  long long x;
  long long y;
  Point(){}
  Point(long long x, long long y)
    :x(x)
    ,y(y) {

    }
};

long long cnt_white_between(const Point &a, const Point &b) {
  bool lef_corner_white = (a.x % 2) == (a.y % 2);
  return ((b.x - a.x + 1) * (b.y - a.y + 1) + lef_corner_white) / 2;
}

long long cnt_black_between(const Point &a, const Point &b) {
  return (b.x - a.x + 1) * (b.y - a.y + 1) - cnt_white_between(a, b);
}

bool no_intersect(
    Point &a1,
    Point &b1,
    Point &a2,
    Point &b2
    ) {
  // cout << b1.x << " " << a2.x << ", " << b2.x << " " << a1.x << endl;
  // cout << b1.y << " " << a2.y << ", " << b2.y << " " << a1.y << endl;

  return b1.x < a2.x || b2.x < a1.x ||
    b1.y < a2.y || b2.y < a1.y;
}

bool first_inside_second(
    Point &a1,
    Point &b1,
    Point &a2,
    Point &b2
    ) {

  return a1.x >= a2.x && b1.x <= b2.x &&
    a1.y >= a2.y && b1.y <= b2.y;
}

bool second_inside_first(
    Point &a1,
    Point &b1,
    Point &a2,
    Point &b2
    ) {
  return a1.x <= a2.x && b1.x >= b2.x &&
    a1.y <= a2.y && b1.y >= b2.y;
}

bool intersect(
    Point &a1,
    Point &b1,
    Point &a2,
    Point &b2
    ) {
  return !no_intersect(a1, b1, a2, b2) && !first_inside_second(a1, b1, a2, b2) &&
    !second_inside_first(a1, b1, a2, b2);
}

pair<Point, Point> intersection(Point &a1, Point &b1, Point &a2, Point &b2) {
  Point a3, b3;
  a3.x = max(a1.x, a2.x);
  b3.x = min(b1.x, b2.x);

    a3.y = max(a1.y, a2.y);
    b3.y = min(b1.y, b2.y);
  return make_pair(a3, b3);
}

int main() {
  int t;
  cin >> t;
  int n, m;
  for (int i = 0; i < t; ++i) {
    cin >> n >> m;
    int x1, y1, x2, y2;
    int x3, y3, x4, y4;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> x3 >> y3 >> x4 >> y4;
    Point a1 = Point(x1, y1);
    Point b1 = Point(x2, y2);
    Point a2 = Point(x3, y3);
    Point b2 = Point(x4, y4);

    // cout << "no_inter: " << no_intersect(a1, b1, a2, b2) << endl;
    // cout << "first_in_sec: " << first_inside_second(a1, b1, a2, b2) << endl;
    // cout << "sec_in_first: " << second_inside_first(a1, b1, a2, b2) << endl;
    // cout << "inter: " << intersect(a1, b1, a2, b2) << endl;
    // if (intersect(a1, b1, a2, b2)) {
    //   auto r = intersection(a1, b1, a2, b2);
    //   // cout << "inrersection: (" << r.first.x << ", " << r.first.y << ") (" <<
    //     r.second.x << ", " << r.second.y << ")\n";
    // }

    long long init_white = cnt_white_between(Point(1, 1), Point(m, n));
    long long init_black = cnt_black_between(Point(1, 1), Point(m, n));
    if (no_intersect(a1, b1, a2, b2)) {
      init_white += cnt_black_between(a1, b1);
      init_black -= cnt_black_between(a1, b1);
      init_black += cnt_white_between(a2, b2);
      init_white -= cnt_white_between(a2, b2);
    } else if (first_inside_second(a1, b1, a2, b2)) {
      init_black += cnt_white_between(a2, b2);
      init_white -= cnt_white_between(a2, b2);
    } else if (second_inside_first(a1, b1, a2, b2)) {
      long long white_around = cnt_white_between(a1, b1) - cnt_white_between(a2, b2);
      long long black_around = cnt_black_between(a1, b1) - cnt_black_between(a2, b2);
      init_white += black_around;
      init_black -= black_around;
      init_white -= cnt_white_between(a2, b2);
      init_black += cnt_white_between(a2, b2);
    } else {
      auto r = intersection(a1, b1, a2, b2);
      init_white += cnt_black_between(a1, b1);
      init_black -= cnt_black_between(a1, b1);
      init_black += cnt_white_between(a2, b2);
      init_white -= cnt_white_between(a2, b2);

      init_white -= cnt_black_between(r.first, r.second);
      init_black += cnt_black_between(r.first, r.second);
    }
    cout << init_white << " " << init_black << "\n";
  }
  return 0;
}
