#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 300005;
const long long INF = 1000000000 * 1ll * 1000000000;

struct Edge {
  int from, to;
  int w;
  int id;
  Edge() {};
  Edge(int from, int to, int w, int id): from(from), to(to), w(w), id(id) {};
  Edge& reverse() {
    swap(from, to);
    return *this;
  }
};


long long d[MAXN];
Edge p[MAXN]; // p[i] -- edge was used to get to i from some vertex & at min cost
vector<Edge> g[MAXN];

void solve_w_dijkstra(int n, int k) {
  vector<int> found_vertices;
  std::fill(d, d + n + 1, INF);
  d[1] = 0;
  set<pair<long long, int>> st;
  st.insert({d[1], 1});
  while (!st.empty() && found_vertices.size() < k + 1) {
    auto it = st.begin();
    long long cur_d = it->first;
    int cur_v = it->second;
    st.erase(it);
    found_vertices.push_back(cur_v);
    for (const auto &e: g[cur_v]) {
      if (d[e.to] > cur_d + e.w) {
        st.erase({d[e.to], e.to});
        d[e.to] = cur_d + e.w;
        p[e.to] = e;
        st.insert({d[e.to], e.to});
      }
    }
  }

  // print ans
  cout << max(0, (int)found_vertices.size() - 1) << "\n";
  for (int i = 1; i < found_vertices.size(); ++i) {
    cout << p[found_vertices[i]].id << " ";
  }
  cout << "\n";
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    Edge e(u, v, w, i + 1);
    g[u].push_back(e);
    g[v].push_back(e.reverse());
  }
  solve_w_dijkstra(n, k);
  return 0;
}
