#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;


const int MAX_N = 302080;
const long long INF = 1e18;

long long max_subc = -INF;
int k = 0;
long long f[MAX_N];
int a[MAX_N];
vector<int> g[MAX_N];

void dfs(int v, int p, bool second_run=false) {
  f[v] = a[v];
  for (auto to: g[v]) {
    if (to != p) {
      dfs(to, v, second_run);
      f[v] += max(0ll, f[to]);
    }
  }

  if (!second_run) {
    max_subc = max(max_subc, f[v]);
  } else {
    if (f[v] == max_subc) {
      ++k;
      f[v] = 0;
    }
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n - 1; ++i) {
    int v, u;
    scanf("%d%d", &v, &u);
    --v; --u;
    g[v].push_back(u);
    g[u].push_back(v);
  }

  dfs(0, -1);
  dfs(0, -1, true);

  cout << max_subc * k << " " << k << "\n";
  return 0;
}
