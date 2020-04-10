#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <unordered_map>

using namespace std;

const int MAXN = 300005;

struct pair_hash {
  int operator() (const pair<int, int> &p) const {
    return p.first ^ p.second;
  }
};

struct Dsu {
  vector<int> p;
  vector<int> rank;
  Dsu(int n): rank(n + 1, 1), p(n + 1) {
    for (int i = 0; i <= n; ++i) {
      p[i] = i;
    }
  }

  int find_set(int x) {
    if (p[x] == x) {
      return x;
    }
    return p[x] = find_set(p[x]);
  }

  void unite_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
      if (rank[x] < rank[y]) {
        swap(x, y);
      }
      p[y] = x;
      rank[x] += rank[y];
    }
  }

};

vector<pair<int, pair<int, int>>> edges;
unordered_map<pair<int, int>, pair<int, int>, pair_hash> mp; // maps edge to its idx u < v
vector<int> g[MAXN]; // spanning tree graph
bool used[MAXN];

void topsort(int v, vector<int> &res) {
  used[v] = true;
  for (auto to: g[v]) {
    if (!used[to]) {
      topsort(to, res);
      res.push_back(mp[{v, to}].first);
    }
  }
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges.push_back({w, make_pair(u, v)});
    if (!mp.count({u, v}) || mp[{u, v}].second > w) {
      mp[{u, v}] = {i + 1, w};
      mp[{v, u}] = {i + 1, w};
    }
  }
  sort(edges.begin(), edges.end());
  Dsu dsu(n);

  // we erase all but n - 1 edges
  for (auto &e: edges) {
    int u = e.second.first;
    int v = e.second.second;
    if (dsu.find_set(u) != dsu.find_set(v)) {
      dsu.unite_sets(u, v);
      g[u].push_back(v);
      g[v].push_back(u);
    }
  }

  // n - 1 topsorted edges
  vector<int> topsorted;
  topsort(1, topsorted);

  printf("%d\n", min(n - 1, k));
  for (int i = 0; i < min(n - 1, k); ++i) {
    printf("%d ", *(topsorted.rbegin() + i));
  }
  printf("\n");

  return 0;
}
