#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int INF = 1e9 + 5;

struct Road {
  int id;
  int from;
  int to;
  int cost;
  Road(int id, int from, int to, int cost): id(id), from(from), to(to), cost(cost) {};
};

vector<Road> g[MAXN];
int color[MAXN];

void prepare_color(int n) {
  for (int i = 0; i < n; ++i) {
    color[i] = 0;
  }
}

bool dfs(int v, int cost, vector<int> &topsort, vector<Road> &skipped_roads) {
  color[v] = 1;
  for (auto &road: g[v]) {
    if (road.cost <= cost) {
      skipped_roads.push_back(road);
    } else if (color[road.to] == 1) {
      return false;
    } else if (color[road.to] == 0) {
      if (!dfs(road.to, cost, topsort, skipped_roads)) {
        return false;
      }
    }
  }

  color[v] = 2;
  topsort.push_back(v);
  return true;
}

bool check(int n, int bound, vector<int> &reversed_roads) {
  prepare_color(n);
  vector<int> topsort;
  vector<Road> skipped_roads;
  for (int i = 0; i < n; ++i) {
    if (color[i] == 0) {
      if (!dfs(i, bound, topsort, skipped_roads)) {
        return false;
      }
    }
  }

  reverse(topsort.begin(), topsort.end());
  vector<int> ord(n);
  for (int i = 0; i < n; ++i) {
    ord[topsort[i]] = i;
  }

  for (auto &road: skipped_roads) {
    if (ord[road.from] > ord[road.to]) {
      reversed_roads.push_back(road.id);
    }
  }

  return true;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v, cost;
    scanf("%d%d%d", &u, &v, &cost);
    --u; --v;
    g[u].push_back(Road(i + 1, u, v, cost));
  }

  int res = INF;
  vector<int> ans;

  int l = 0;
  int r = res;
  while (l <= r) {
    int mm = (l + r) / 2;
    vector<int> cur_ans;
    if (check(n, mm, cur_ans)) {
      if (mm < res) {
        res = mm;
        swap(ans, cur_ans);
      }
      r = mm - 1;
    } else {
      l = mm + 1;
    }
  }

  cout << res << " " << ans.size() << "\n";
  if (ans.size()) {
    for (auto el: ans) {
      cout << el << " ";
    }
    cout << "\n";
  }

  return 0;
}
