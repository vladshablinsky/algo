#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  long long n;
  cin >> n;
  cout << -n + 1 << " " << n << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
