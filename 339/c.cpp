#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

const double PI = acos(-1);

long long sqr(long long x) {
  return x * x;
}

int main() {
  long long min_r = 1e18;
  long long max_r = 0;
  int n;
  cin >> n;
  long long x, y;
  cin >> x >> y;
  for (int i = 0; i < n; ++i) {
    long long x_i, y_i;
    cin >> x_i >> y_i;
    long long r = sqr(x_i-x) + sqr(y_i-y);
    min_r = min(min_r, r);
    max_r = max(max_r, r);
  }

  double ans = PI * (max_r - min_r);
  cout << fixed << setprecision(20) << ans << "\n";

  return 0;
}
