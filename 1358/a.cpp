#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  cout << (n * m + 1) / 2 << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
