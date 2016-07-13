#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <string>
#include <cmath>

using namespace std;

const double eps = 1e-9;
const double PI = acos(-1);

int main() {
  double d, h, v, e;
  cin >> d >> h >> v >> e;

  double ans = (h * PI * d * d / 4.) / (v - e * PI * d * d / 4);
  if (ans + eps < 0) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    printf("%.16lf\n", ans);
  }
  return 0;
}
