#include <iostream>
#include <cstdio>

using namespace std;

bool solve() {
  int n, m, k;
  cin >> n >> m >> k;
  return (k == (n * m - 1));
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
