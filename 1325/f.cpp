//#pragma comment(linker, "/stack:200000000")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

const int MAXN = 100005;
vector<int> g[MAXN];
vector<int> dfs_tree_path;
int lvl[MAXN];
int rt;

unordered_set<int> forbidden;
vector<int> independent;

void ans_2_ready(int cnt) {
  printf("2\n%d\n", cnt);
  for (int i = 0; i < cnt; ++i) {
    printf("%d ", *(dfs_tree_path.rbegin() + i));
  }
  printf("\n");
}

void ans_1_ready() {
  printf("1\n");
  for (int i = 0; i < rt; ++i) {
    printf("%d ", independent[i]);
  }
  printf("\n");
}

void dfs(int v) {
  dfs_tree_path.push_back(v);
  lvl[v] = dfs_tree_path.size();

  for (auto to: g[v]) {

    if (!lvl[to]) {
      dfs(to);
    } else if (lvl[v] - lvl[to] + 1 >= rt) { // (v, to) is a back-edge
      ans_2_ready(lvl[v] - lvl[to] + 1);
      exit(0);
    }
  }

  if (!forbidden.count(v)) {
    independent.push_back(v);
    for (auto to: g[v]) {
      forbidden.insert(to);
    }
  }

  dfs_tree_path.pop_back();
}

int main() {
  //freopen("input.txt", "r", stdin);
  int n, m;
  scanf("%d%d", &n, &m);
  rt = ceil(sqrt(n));

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  dfs(1);
  ans_1_ready();
  return 0;
}
