#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  long long s, a, b, c;
  cin >> s >> a >> b >> c;
  cout << s / c + ((s / c) / a) * b << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
