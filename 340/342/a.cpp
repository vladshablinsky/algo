#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const long double eps = 1e-6;

long long n;
long long a, b, c;

bool check(long double k) {

  cout << "CHECK FOR " << k << endl;
  cout << "LEFT " << (long long) ((long double)(n) - k * (b - c)) << endl;
  cout << "B IS " << b << endl;
  cout << ((long double)(n) - k * (b - c) + eps) << endl;

  return ((long double)(n) - k * (b - c) + eps > b);
}

int main() {
  cout << (((long long) 1e18) == ((long long)(1e18 + 1))) << endl;
  cin >> n;
  cin >> a >> b >> c;

  long long l = 0;
  long long r = 1e18;
  long long k = 0;

  while (l <= r) {
    long long m = l + (r - l) / 2;
    if (check(m)) {
      k = max(k, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  cout << endl;
  cout << "K IS " << k << endl;

  if (n >= b) {
    ++k;
  }

  cout << max(n / a + (n - a * (n / a)) / b, k + (n - k * (b - c)) / a) << "\n";

  return 0;
}
