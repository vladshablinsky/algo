#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const long long MOD = 998244353;
long long a[MAXN];
long long b[MAXN];
long long ans = 0;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    a[i] *= (i + 1) * 1ll * (n - i);
  }

  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  sort(a, a + n);
  sort(b, b + n);

  for (int i = 0; i < n; ++i) {
    ans = (ans + (a[i] % MOD) * b[n - i - 1]) % MOD;
  }
  cout << ans << "\n";
  return 0;
}
