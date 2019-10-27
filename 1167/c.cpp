#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 500005;
const int MAX_ALL = MAX_N * 2;
int spreads[MAX_ALL];
int n, m;

vector<int> g[MAX_ALL];
vector<int> cur_component;
int cnt_groups;

void dfs(int x) {
  cur_component.push_back(x);
  if (x >= n) {
    ++cnt_groups;
  }
  for (int to: g[x]) {
    if (spreads[to] == 0) {
      spreads[to] = 1;
      dfs(to);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; ++j) {
      int cur_user;
      scanf("%d", &cur_user);
      --cur_user;
      g[n + i].push_back(cur_user);
      g[cur_user].push_back(n + i);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (!spreads[i]) {
      spreads[i] = 1;
      dfs(i);
      int spread = cur_component.size() - cnt_groups;
      for (int el: cur_component) {
        spreads[el] = spread;
      }
      cur_component.clear();
      cnt_groups = 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d ", spreads[i]);
  }
  printf("\n");

  return 0;
}
