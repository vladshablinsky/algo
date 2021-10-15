#include <iostream>
#include <cstdio>

using namespace std;

bool is_prime(int x) {
  if (x < 4) {
    return true;
  }
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

void solve() {
  int d;
  cin >> d;
  int p = d + 1;
  for (; !is_prime(p); ++p) {}
  int q = p + d;
  for (; !is_prime(q); ++q) {}
  cout << p * q << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
