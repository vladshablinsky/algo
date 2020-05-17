#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 3.14159265358979323846;
const double EPS = 1e-6;
const int ITER = 10000;

double find_ans(double x, double angle) {
  double l = x / sqrt(2.);
  double r = x;
  double ans = r;
  int cur_iter = 0;
  while (cur_iter < ITER) {
    ++cur_iter;
    double m = (l + r) / 2.;
    double alpha = acos(m / x);
    double bound = cos(alpha - angle/2) * x;
    int c;
    //cin >> c;
    if (bound + EPS < m) {
      ans = min(ans, m);
      r = m;
    } else {
      l = m;
    }
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;
  double angle = PI / n;
  //cout << angle / PI * 180 << endl;
  double x = sqrt(1. / (-cos(angle) + 1) / 2);
  //cout << x << endl;

  if (n & 1) {
    printf("%.8f\n", find_ans(x, angle) * 2);
  } else {
    printf("%.8f\n", sqrt(x * x - 0.25) * 2);
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
