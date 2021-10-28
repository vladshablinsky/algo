#include <iostream>

using namespace std;

bool solve() {
  string a;
  string b;
  int n;
  cin >> n;
  cin >> a;
  cin >> b;
  for (int i = 0; i < n; ++i) {
    if (a[i] == b[i] && a[i] == '1') {
      return false;
    }
  }
  return true;
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
