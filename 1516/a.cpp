#include <iostream>

using namespace std;

void solve() {
  int sum = 0;
  int n;
  int ops;
  cin >> n >> ops;
  int el;
  for (int i = 0; i < n - 1; ++i) {
    cin >> el;
    if (ops >= el) {
      sum += el;
      ops -= el;
      cout << 0 << " ";
    } else {
      el -= ops;
      sum += ops;
      cout << el << " ";
      ops = 0;
    }
  }
  cin >> el;
  cout << el + sum << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
