#include <iostream>
#include <cstdio>

using namespace std;

const int MOD = 1000000007;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  long long cur_pow = 1;
  long long ans = 0;
  for (int i = 0; i < 32; ++i) {
    if (k & (1 << i)) {
      ans += cur_pow;
      ans %= MOD;
    }

    cur_pow *= n;
    cur_pow %= MOD;
  }
  cout << ans << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
