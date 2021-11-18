#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);

  int ans = 0;
  ans += (n / 3) * m;
  ans += (m / 3) * (n % 3);
  ans += (1 + (n % 3) * (m % 3)) / 2;
  cout << ans << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
