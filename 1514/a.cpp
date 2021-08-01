#include <iostream>
#include <cmath>

using namespace std;

bool is_square_x(int x) {
  for (int i = 0; i * i <= x; ++i) {
    if (i * i == x) {
      return true;
    }
  }
  return false;
}

void solve() {
  int n;
  cin >> n;
  bool all_squares = true;
  for (int i = 0; i < n; ++i) {
    int a_i;
    cin >> a_i;
    all_squares &= is_square_x(a_i);
  }
  if (all_squares) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
