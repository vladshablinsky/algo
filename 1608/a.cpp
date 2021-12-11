#include <iostream>

using namespace std;

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cout << i + 1 << " ";
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
