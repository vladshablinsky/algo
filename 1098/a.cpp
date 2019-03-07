#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 4;
int n;
vector<int> g[MAXN];
int s[MAXN];

long long dfs(int v, int p, long long val, bool odd) {
  if ((s[v] == -1 && odd) || (s[v] != -1 && !odd)) {
    return -1;
  }
  if (s[v] == -1) {
    s[v] = s[p];
  }

  cout << "v: " << v << ", p: " << p << ", val: " << val << endl;

  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (s[to] != -1 && s[to] < s[p]) {
      return -1;
    } else {
      int res_subtree = -1;
      if (s[to] == -1) {
        res_subtree = dfs(to, v, 0, !odd);
      } else {
        res_subtree = dfs(to, v, s[to] - s[v], !odd);
      }

      if (res_subtree == -1) {
        return -1;
      } else {
        val += res_subtree;
      }
    }
  }
  return val;
}

int main() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int from;
    cin >> from;
    g[from - 1].push_back(i);
  }

  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  cout << dfs(0, 0, s[0], true) << "\n";
  return 0;
}
