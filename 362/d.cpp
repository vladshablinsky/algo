#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;

int n;
vector<int> g[MAX_N];
double ans[MAX_N];

// returns size of subtree v
int dfs(int v, int depth) {
  int subtree_size = 1;
  for (int i = 0; i < g[v].size(); ++i) {
    subtree_size += dfs(g[v][i], depth + 1);
  }
  ans[v] = (n - depth - subtree_size + 1) / 2. + depth;
  return subtree_size;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int parent_of_i;
    scanf("%d", &parent_of_i);
    --parent_of_i;
    g[parent_of_i].push_back(i);
  }

  dfs(0, 1);
  for (int i = 0; i < n; ++i) {
    printf("%.7lf ", ans[i]);
  }
  printf("\n");
  return 0;
}
