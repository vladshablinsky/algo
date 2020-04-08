#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i == n - 1 && j == m - 1) {
        cout << 'W';
      } else {
        cout << 'B';
      }
    }
    cout << "\n";
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
