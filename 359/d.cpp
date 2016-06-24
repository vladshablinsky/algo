#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = 3e5 + 10;
vector<int> g[MAXN];
int parent[MAXN];
/* centroid in i-th subtree */
int centroid[MAXN];
int subtree_size[MAXN];
int n, q;


void dfs(int v) {
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    dfs(to);
    //printf("CENTROID OF %d is %d\n", to, centroid[to]);
    //printf("SUBTREE_SIZE OF %d is %d\n", to, subtree_size[to]);
  }

  int cur_subtree_size = 0;
  int max_son_subtree_size = -1;
  int max_son_subtree_vertex = -1;
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    cur_subtree_size += subtree_size[to];
    if (max_son_subtree_size < subtree_size[to]) {
      max_son_subtree_size = subtree_size[to];
      max_son_subtree_vertex = to;
    }
  }

  ++cur_subtree_size;
  subtree_size[v] = cur_subtree_size;
  //cout << "SUBTREE SIZE ___ OF ___ " << v + 1 << " IS " << subtree_size[v] << endl;

  if (max_son_subtree_vertex == -1 || max_son_subtree_size <= cur_subtree_size / 2) {
    centroid[v] = v;
    return;
  }

  int cur_centroid = centroid[max_son_subtree_vertex];

  while (cur_subtree_size - subtree_size[cur_centroid] > cur_subtree_size / 2) {
    cur_centroid = parent[cur_centroid];
  }
  centroid[v] = cur_centroid;
}

int main() {
  scanf("%d%d", &n, &q);

  for (int i = 1; i < n; ++i) {
    int t;
    scanf("%d", &t);
    --t;
    g[t].push_back(i);
    parent[i] = t;
  }
  parent[0] = -1;

  dfs(0);

  for (int i = 0; i < q; ++i) {
    int query_v;
    scanf("%d", &query_v);
    printf("%d\n", centroid[query_v - 1] + 1);
  }

  return 0;
}
