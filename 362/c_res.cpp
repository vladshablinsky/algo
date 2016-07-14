#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>

using namespace std;

map<long long, long long> edge_cost;

void add_path(long long u, long long v, int w) {
  while (u != v) {
    if (u < v) {
      edge_cost[v] += w;
      v /= 2;
    } else {
      edge_cost[u] += w;
      u /= 2;
    }
  }
}

long long query(long long u, long long v) {
  long long ans = 0;
  while (u != v) {
    if (u < v) {
      ans += edge_cost[v];
      v /= 2;
    } else {
      ans += edge_cost[u];
      u /= 2;
    }
  }
  return ans;
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int query_id;
    long long u, v;
    cin >> query_id;
    if (query_id == 1) {
      int w;
      cin >> u >> v >> w;
      add_path(u, v, w);
    } else {
      cin >> u >> v;
      cout << query(u, v) << "\n";
    }
  }
  return 0;
}

