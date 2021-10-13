#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  cin >> n;
  int d = 9;
  cout << d;
  --d;
  for (int i = 0; i < n - 1; ++i) {
    cout << d;
    d++;
    d %= 10;
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
