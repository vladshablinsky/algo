#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000000000;

void solve() {
  int n;
  cin >> n;

  int x = 1;
  for (int i = 0; i < 31; ++i) {
    if (n & (1 << i)) {
      x = 1 << i;
    }
  }
  cout << x - 1 << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
