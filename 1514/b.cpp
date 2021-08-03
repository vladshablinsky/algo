#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MOD = 1000000007;

void solve() {
  int n, k;
  cin >> n >> k;

  int ans = 1;
  for (int i = 0; i < k; ++i) {
    ans = (ans * 1ll * n) % MOD;
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
