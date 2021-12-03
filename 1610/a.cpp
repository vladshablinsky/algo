#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  if (n == 1 || m == 1) {
    cout << 1 - (n == m);
  } else {
    cout << 2;
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
