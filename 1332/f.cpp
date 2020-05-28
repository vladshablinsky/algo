#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int MOD = 998244353;
vector<int> g[MAXN];
int combine_f_g_in_child[MAXN];

int binpow(int x, int pow) {
  if (pow == 0) {
    return 1;
  } else {
    if (pow & 1) {
      return (x * 1ll * binpow(x, pow - 1)) % MOD;
    } else {
      long long res = binpow(x, pow / 2);
      return (res * res) % MOD;
    }
  }
}

int modadd(int x, int y) {
  return (x + y) % MOD;
}

pair<int, int> dfs(int v, int p) {
  // leaf
  if (g[v].size() == 1 && p != -1) {
    //cout << "YO: " << v << endl;
    return {0, 0};
  }

  combine_f_g_in_child[v] = 1;
  int product_f_g = 1;
  int product_f_2g = 1;
  int product_magic = 1;
  for (auto to: g[v]) {
    if (to != p) {
      auto res = dfs(to, v);
      //cout << "f(" << to << ") = " << res.first << " ";
      //cout << "g(" << to << ") = " << res.second << "\n";

      int combined_for_f = modadd(combine_f_g_in_child[to], combine_f_g_in_child[to]);
      int combined_for_g = modadd(combined_for_f, combine_f_g_in_child[to]);

      //cout << "combined_for_f: " << combined_for_f << ", combined_for_g: " << combined_for_g << endl;

      product_f_g = (product_f_g * 1ll * (
            modadd(res.first, res.second) + 1)
          ) % MOD;
      product_f_2g = (product_f_2g * 1ll * (
              modadd(res.first, modadd(res.second, res.second)) + 2)
          ) % MOD;

      product_magic = (product_magic * 1ll * (
          modadd(
            combine_f_g_in_child[to],
            modadd(modadd(res.first, res.first), modadd(res.second, res.second)) + 3))
        ) % MOD;

      combine_f_g_in_child[v] = (combine_f_g_in_child[v] * 1ll * (res.first + res.second + 1)) % MOD;
    }
  }

  combine_f_g_in_child[v] -= 1;
  combine_f_g_in_child[v] += MOD;
  combine_f_g_in_child[v] %= MOD;

  int cur_f = (product_f_2g - product_f_g + MOD) % MOD;
  int cur_g = (product_magic - 1 + MOD) % MOD;
  return {cur_f, cur_g};
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto res = dfs(1, -1);
  //cout << "f(" << 1 << ") = " << res.first << " ";
  //cout << "g(" << 1 << ") = " << res.second << "\n";
  cout << (res.first + res.second) % MOD << "\n";
  return 0;
}
