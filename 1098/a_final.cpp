#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;
const long long INF = 1e18;

int n;
vector<int> g[MAX_N];
long long s[MAX_N];

long long dfs(int v, int p) {
  long long ans = 0;
  if (s[v] == -1) {
    s[v] = INF;
    for (int to: g[v]) {
      if (s[to] < s[p]) {
        return -1;
      } else {
        s[v] = min(s[v], s[to]);
      }
    }
    if (s[v] == INF) {
      s[v] = s[p];
    }
  }

  for (int to: g[v]) {
    long long cur_sub_tree = dfs(to, v);
    if (cur_sub_tree == -1) {
      return -1;
    } else {
      ans += cur_sub_tree;
    }
  }

  if (v == 0) {
    return ans + s[v];
  } else {
    return s[v] - s[p] + ans;
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n - 1; ++i) {
    int t;
    cin >> t;
    g[t - 1].push_back(i);
  }

  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  cout << dfs(0, 0) << "\n";
  return 0;
}
