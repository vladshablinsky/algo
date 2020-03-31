#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_X = 998244353;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void solve(int ang) {
  int to_div = gcd(180, ang);

  int factor = 1;
  int cur_x;
  for (int factor = 1; (cur_x = 180 / to_div * factor) < MAX_X; ++factor) {
    if (ang / to_div * factor <= cur_x - 2) {
      cout << cur_x << "\n";
      return;
    }
  }
  cout << "-1\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int ang;
    cin >> ang;
    solve(ang);
  }
  return 0;
}
