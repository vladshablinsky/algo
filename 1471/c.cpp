#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 300005;
int k[MAXN];
int c[MAXN];

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &k[i]);
    --k[i];
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &c[i]);
  }

  sort(k, k + n);
  long long res = 0;
  int p1 = 0;
  for (int i = n - 1; i >= 0; --i) {
    if (p1 < m && p1 <= k[i] && c[p1] <= c[k[i]]) {
      res += c[p1];
      ++p1;
    } else {
      res += c[k[i]];
    }
  }

  printf("%lld\n", res);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
