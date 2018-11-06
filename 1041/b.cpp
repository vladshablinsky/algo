#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
  if (b) {
    return gcd(b, a % b);
  } else {
    return a;
  }
}

int main() {
  long long a, b, x, y;
  cin >> a >> b >> x >> y;

  long long gcd_xy = gcd(x, y);
  x /= gcd_xy;
  y /= gcd_xy;

  cout << min (a / x, b / y) << "\n";
  return 0;
}
