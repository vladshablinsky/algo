#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <cmath>

using namespace std;

struct Point {
  double x, y;
  int id;
  Point(): x(0), y(0), id(0) {};
  Point(double x, double y, int id): x(x), y(y), id(id) {};
};

vector<Point> p;
vector<Point> sorted_from_a;
vector<Point> sorted_from_b;

Point a_p;
Point b_p;
Point t_p;
double a_x, a_y, b_x, b_y, t_x, t_y;

double sqr(double x) {
  return x * x;
}

double d_betw(Point a, Point b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

bool cmp(Point p_1, Point p_2) {
  return d_betw(t_p, p_1) > d_betw(t_p, p_2);
}

bool cmp_a(Point p_1, Point p_2) {
  return d_betw(a_p, p_1) - d_betw(t_p, p_1) < d_betw(a_p, p_2) - d_betw(t_p, p_2);
}

bool cmp_b(Point p_1, Point p_2) {
  return d_betw(b_p, p_1) - d_betw(t_p, p_1) < d_betw(b_p, p_2) - d_betw(t_p, p_2);
}

int main() {
  int n;
  cin >> a_x >> a_y >> b_x >> b_y >> t_x >> t_y;
  cin >> n;

  a_p = Point(a_x, a_y, -1);
  b_p = Point(b_x, b_y, -1);
  t_p = Point(t_x, t_y, -1);

  double res_from_t = 0;

  for (int i = 0; i < n; ++i) {
    long long xx, yy;
    cin >> xx >> yy;
    p.push_back(Point(xx, yy, i + 1));
    res_from_t += d_betw(t_p, p.back());
  }

  res_from_t *= 2.;

  sorted_from_a = p;
  sorted_from_b = p;
  sort(sorted_from_a.begin(), sorted_from_a.end(), cmp_a);
  sort(sorted_from_b.begin(), sorted_from_b.end(), cmp_b);

  double ans = 1e18;

  //cout << "from_t : " << res_from_t << endl;

  for (int i = 0; i < min(n, 2); ++i) {
    for (int j = 0; j < min(n, 2); ++j) {
      if (sorted_from_a[i].id != sorted_from_b[j].id) {
        double cur_dist = res_from_t - d_betw(sorted_from_a[i], t_p) + d_betw(sorted_from_a[i], a_p) -
          d_betw(sorted_from_b[j], t_p) + d_betw(sorted_from_b[j], b_p);
        ans = min(ans, cur_dist);
      }
    }
    double dist_only_a = res_from_t - d_betw(sorted_from_a[i], t_p) + d_betw(sorted_from_a[i], a_p);
    double dist_only_b = res_from_t - d_betw(sorted_from_b[i], t_p) + d_betw(sorted_from_b[i], b_p);
    ans = min(ans, dist_only_a);
    ans = min(ans, dist_only_b);
  }

  printf("%.7lf\n", ans);
  return 0;
}
