#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int MOD = 1e9 + 7;

bool used[MAXN];
vector<int> g[MAXN];

int binpow(int x, int k) {
  if (k == 0) {
    return 1;
  }

  if (k & 1) {
    return (x * 1ll * binpow(x, k - 1)) % MOD;
  } else {
    int res = binpow(x, k / 2);
    return (res * 1ll * res) % MOD;
  }
}

int dfs(int v) {
  used[v] = true;
  int ans = 1;
  for (auto to: g[v]) {
    if (!used[to]) {
      ans += dfs(to);
    }
  }
  return ans;
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n - 1; ++i) {
    int u, v, is_black;
    scanf("%d%d%d", &u, &v, &is_black);
    --u;
    --v;

    if (!is_black) {
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  int cnt_bad = 0;
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      cnt_bad = (cnt_bad + binpow(dfs(i), k)) % MOD;
    }
  }

  cout << (binpow(n, k) - cnt_bad + MOD) % MOD << "\n";
  return 0;
}
