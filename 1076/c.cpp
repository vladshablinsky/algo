#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-6;

void solve() {
  int d;
  cin >> d;
  if (d * (d - 4) < 0) {
    printf("N\n");
    return;
  }
  double dis = d * (d - 4);
  double root1 = (sqrt(dis) + d) / 2.;
  double root2 = (-sqrt(dis) + d) / 2.;

  if (root1 - EPS < d && root1 + EPS > 0) {
    printf("Y %.10lf %.10lf\n", root1, -root1 + d);
  } else if (root2 - EPS < d && root2 - EPS > 0) {
    printf("Y %.10lf %.10lf\n", root2, -root2 + d);
  } else {
    printf("N\n");
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
