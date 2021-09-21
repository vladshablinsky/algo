#include <iostream>
#include <algorithm>

using namespace std;

bool solve() {
  int n;
  cin >> n;
  bool possible = true;
  long long rem = 0;
  for (int i = 0; i < n; ++i) {
    long long sz;
    cin >> sz;
    sz += rem;
    if (sz < i) {
      possible = false;
    }
    rem = sz - i;
  }
  return possible;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
