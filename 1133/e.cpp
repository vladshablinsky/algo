#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5005;
const int DIFF = 5;

int a[MAXN];
pair<int, int> g[MAXN]; // g(i) is cnt and idx of last of studs we can take if begin in i
int u[MAXN]; // u(i) is max k so that g(k) < i
int f[MAXN][MAXN]; // f(i,j) is max cnt of studs if j'th group begins at i
int mx_prev_layer[MAXN];

int n, k;

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);

  int l = 0;
  for (int r = 0; r < n; ++r) {
    while (a[r] - a[l] > DIFF) {
      g[l] = {r - l, r - 1};
      ++l;
    }
  }
  while (l < n) {
    g[l] = {n - l, n - 1};
    ++l;
  }

  int cur_k = -1;
  for (int i = 0; i < n; ++i) {
    while (g[cur_k + 1].second < i) {
      ++cur_k;
    }
    u[i] = cur_k;
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    f[1][i] = g[i].first;
    mx_prev_layer[i] = max(i - 1 >= 0 ? mx_prev_layer[i - 1]: 0, f[1][i]);
  }
  ans = max(ans, mx_prev_layer[n - 1]);

  for (int j = 2; j <= k; ++j) {
    for (int i = 0; i < n; ++i) {
      if (u[i] >= 0) { // if it does not make sense to start j'th block at i, skip it
        f[j][i] = g[i].first + mx_prev_layer[u[i]];
      }
    }
    for (int i = 0; i < n; ++i) {
      mx_prev_layer[i] = max(i - 1 >= 0 ? mx_prev_layer[i - 1]: 0, f[j][i]);
    }
    ans = max(ans, mx_prev_layer[n - 1]);
  }

  cout << ans << "\n";
  return 0;
}
