#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int sum_digits(long long x) {
  int res = 0;
  while (x != 0) {
    res += x % 10;
    x /= 10;
  }
  return res;
}

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long x;
    cin >> x;
    while (gcd(x, sum_digits(x)) == 1) {
      ++x;
    }
    cout << x << "\n";
  }
}
