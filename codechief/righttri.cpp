#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

long double eps = 1e-9;

long double mabs(long double x) {
  if (x + eps < 0) {
    return -x;
  }
  return x;
}

void solve() {
  vector<long double> ans;
  long double c, s;
  cin >> c >> s;
  long double h = 2 * s / c;
  long double sum = sqrt(c * c + 4 * s);

  if (c * c - 4 * s + eps < 0) {
    cout << -1 << "\n";
    return;
  }

  long double a = (sum - sqrt(c * c - 4 * s)) / 2;
  long double b = (sum + sqrt(c * c - 4 * s)) / 2;

  if (a + eps < 0) {
    cout << -1 << "\n";
    return;
  }

  cout << setprecision(20) << a << " " << b << " " << c << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
