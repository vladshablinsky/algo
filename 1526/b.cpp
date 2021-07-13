#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

bool solve(int x) {
  if (x % 11 == 0 || x % 111 == 0) {
    return true;
  }

  // x = 11 * a + 111 * b = 11 * (a + 10 b) + b;
  int b = x % 11;
  int a = (x - b) / 11 - 10 * b;

  // cout << "a: " << a << ", b:" << b << endl;

  return (a >= 0 && b >= 0 && 11 * a + 111 * b == x);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int x;
    cin >> x;
    if (solve(x)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
