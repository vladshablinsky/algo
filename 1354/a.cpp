#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const char nl = '\n';

void solve() {
  long long a, b, c, d;
  cin >> a >> b >> c >> d;
  long long time_slept = b;
  long long time_left = max(0ll, a - b);

  if (time_left == 0) {
    cout << time_slept << nl;
  } else {
    if (c - d <= 0) {
      cout << "-1\n";
    } else {
      cout << time_slept + c * ((time_left + (c - d - 1)) / (c - d)) << nl;
    }
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
