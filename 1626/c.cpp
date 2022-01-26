#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 105;
const int INF = 1000000007;

int k[MAXN];
int h[MAXN];

long long sum(long long to) {
  return to * (to + 1) / 2;
}

void solve() {
  int n;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &k[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }

  long long ans = 0;
  int next_l = INF;
  int prev_r;
  for (int i = n - 1; i >= 0; --i) {
    if (k[i] < next_l) {
      prev_r = k[i];
      ans += sum(h[i]);
      next_l = k[i] - h[i] + 1;
    } else if (h[i] > k[i] - next_l + 1) {
      ans -= sum(prev_r - next_l + 1);
      ans += sum(h[i] + prev_r - k[i]);
      next_l = k[i] - h[i] + 1;
    }
  }

  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
