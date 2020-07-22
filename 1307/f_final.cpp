#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int MAXP = 19;
const int NONE = -1;
const int INF = 1e9;
int n, k, r;

bool is_station[MAXN];
int highest_station[MAXN];
int tin[MAXN];
int tout[MAXN];
int up[MAXN][MAXP];
int depth[MAXN];
pair<int, int> closest_station_dist[MAXN];
int timer = 0;

vector<int> g[MAXN];
vector<int> stations_stack;
int station_id = NONE;

bool is_upper(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
  if (is_upper(a, b)) {
    return a;
  }
  if (is_upper(b, a)) {
    return b;
  }

  for (int i = MAXP - 1; i >= 0; --i) {
    if (!is_upper(up[a][i], b)) {
      a = up[a][i];
    }
  }
  return up[a][0];
}

int distance(int lower, int upper) {
  return depth[lower] - depth[upper];
}

void dfs_closest_station(int v, int p) {
  depth[v] = depth[p] + 1;

  closest_station_dist[v] = {INF, 0};
  if (is_station[v]) {
    closest_station_dist[v] = {0, v};
  }

  for (auto to: g[v]) {
    if (to != p) {
      dfs_closest_station(to, v);
      if (closest_station_dist[to].first + 1 < closest_station_dist[v].first) {
        closest_station_dist[v].first = closest_station_dist[to].first + 1;
        closest_station_dist[v].second = closest_station_dist[to].second;
      }
    }
  }
}

// upper_station_id
void dfs(int v, int p, int upper_station_id=NONE, int cur_fuel=0) {
  tin[v] = timer++;
  up[v][0] = p;

  cout << "in vertex: " << v << ", us: " << upper_station_id << ", fuel: " << cur_fuel << endl;

  if (upper_station_id != NONE && depth[upper_station_id] <= depth[v]) {
    highest_station[v] = upper_station_id;
  } else { // upper station id is NONE!
    highest_station[v] = v;
  }

  if (cur_fuel - closest_station_dist[v].first >= 0) {
    // can go to the station and increase cur_fuel
    cur_fuel = max(cur_fuel, k - closest_station_dist[v].first);
    //if (upper_station_id == NONE) {
    //  upper_station_id = closest_station_dist[v].second;
    //}
  } else if (!cur_fuel && k - closest_station_dist[v].first > 0) {
    upper_station_id = closest_station_dist[v].second;
    cur_fuel = k - closest_station_dist[v].first;
  }

  // cout << "upper when leaving " << v << " is " << upper_station_id << endl;

  for (int j = 1; j < MAXP; ++j) {
    up[v][j] = up[up[v][j - 1]][j - 1];
  }

  for (auto to: g[v]) {
    if (to != p) {
      if (cur_fuel) {
        dfs(to, v, upper_station_id, cur_fuel - 1);
      } else {
        dfs(to, v, NONE);
      }
    }
  }

  tout[v] = timer++;
}

void solve(int low, int high) {
  if (is_upper(low, high)) {
    swap(low, high);
  }

  if (!is_upper(high, low)) {
    low = highest_station[low];
    high = highest_station[high];
  } else {
    low = highest_station[low];
    if (is_upper(low, high)) {
      high = highest_station[high];
    }
  }

  int lca_from_to = lca(low, high);
  // cout << "h_from: " << low << ", h_to: " << high << endl;
  // cout << "lca: " << lca_from_to << ", dist: " << distance(low, lca_from_to) + distance(high, lca_from_to) << endl;
  if (distance(low, lca_from_to) + distance(high, lca_from_to) > k) {
    printf("NO\n");
  } else {
    printf("YES\n");
  }
}

int main() {
  scanf("%d%d%d", &n, &k, &r);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }
  for (int i = 0; i < r; ++i) {
    int v;
    scanf("%d", &v);
    is_station[v] = true;
  }

  dfs_closest_station(1, 1);
  dfs(1, 1);
  // for (int i = 1; i <= n; ++i) {
  //   cout << depth[i] << " ";
  // }
  // cout << endl;
  // for (int i = 1; i <= n; ++i) {
  //   cout << highest_station[i] << " ";
  // }
  // cout << endl;
  // for (int i = 1; i <= n; ++i) {
  //   cout << "( " << closest_station_dist[i].first << ", " << closest_station_dist[i].second << ") ";
  // }
  // cout << endl;

  int q_cnt;
  scanf("%d", &q_cnt);
  for (int i = 0; i < q_cnt; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    solve(from, to);
  }

  return 0;
}
