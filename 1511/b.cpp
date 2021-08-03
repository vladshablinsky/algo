#include <iostream>
#include <cstdio>

using namespace std;

bool is_prime(int x) {
  if (x == 1 || x == 2) {
    return true;
  }
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

int find_next_prime(int k) {
  k++;
  while (!is_prime(k)) {
    ++k;
  }
  return k;
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  // gcd is 10 ^ (c - 1);
  // x is p1 ^ (a - c - 1);
  // y is p2 ^ (b - c - 1);

  int gcd = 1;
  for (int i = 0; i < c - 1; ++i) {
    gcd *= 10;
  }

  int x = 1;
  int y = 1;
  while (a - c) {
    x *= 10;
    --a;
  }
  while (b - c) {
    y *= 10;
    --b;
  }

  x = find_next_prime(x);
  y = find_next_prime(y);
  if (x == y) {
    x = find_next_prime(x);
  }

  cout << x * gcd << " " << y * gcd << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
