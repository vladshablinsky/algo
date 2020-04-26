#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;
const int ITERATIONS = 1000;
const long double EPS = 1e-7;

pair<int, int> points[MAXN];

bool check(long double r, int n) {
  long double intersect_l = -1e15;
  long double intersect_r = 1e15;
  for (int i = 0; i < n; ++i) {
    long double dist_to_y_r = abs(r - 1. * abs(points[i].second));
    if (dist_to_y_r - EPS > r) {
      return false;
    }

    long double half_segment = sqrt(r - dist_to_y_r) * sqrt(r + dist_to_y_r);
    long double ll = - half_segment + 1. * points[i].first;
    long double rr = ll + 2. * half_segment;
    intersect_l = max(intersect_l, ll);
    intersect_r = min(intersect_r, rr);
    if (intersect_l - EPS > intersect_r) {
      return false;
    }
  }
  return true;
}

int main() {
  int n;
  scanf("%d", &n);
  bool above = false;
  bool below = false;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &points[i].first, &points[i].second);
    above |= (points[i].second > 0);
    below |= (points[i].second < 0);
  }

  if (above && below) {
    printf("-1\n");
    return 0;
  }

  long double l = 0;
  long double r = 1e14;
  long double ans = 1e14;
  int iterations = 0;
  while (iterations < ITERATIONS) {
    long double m = l + (r - l) / 2;
    if (check(m, n)) {
      ans = min(ans, m);
      r = m;
    } else {
      l = m;
    }
    ++iterations;
  }
  printf("%.7Lf\n", ans);
  return 0;
}
