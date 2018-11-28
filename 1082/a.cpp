#include <iostream>
#include <cstdio>

using namespace std;

const int INF = 2e9;

int abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int ans_first(int x, int d) {
  return (x - 1 + d - 1) / d;
}

int ans_last(int x, int d, int n) {
  return (n - x + d - 1) / d;
}

int ans(int x, int y, int d) {
  if (abs(x - y) % d == 0) {
    return abs(x - y) / d;
  }
  return INF;
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int n, x, y, d;
    cin >> n >> x >> y >> d;
    if (x == y) {
      cout << 0 << "\n";
    } else {
      int res = ans(x, y, d);
      res = min(res, ans(1, y, d) + ans_first(x, d));
      res = min(res, ans(n, y, d) + ans_last(x, d, n));
      if (res == INF) {
        cout << "-1\n";
      } else {
        cout << res << "\n";
      }
    }
  }
  return 0;
}
