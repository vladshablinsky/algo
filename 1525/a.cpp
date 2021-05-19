#include <iostream>
#include <cstdio>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

void solve() {
  int k;
  cin >> k;
  int water = 100 - k;
  int div = gcd(k, water);
  cout << k / div + water / div << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
