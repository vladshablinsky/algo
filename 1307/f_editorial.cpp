#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 400005;
const int MAXP = 20;
const int INF = 1e9;
int n, k, r;

vector<int> g[MAXN];
vector<int> stations;
bool is_station[MAXN];
int used[MAXN];
int p[MAXN];
int union_rank[MAXN];
int depth[MAXN];
int tin[MAXN];
int tout[MAXN];
int up[MAXN][MAXP];
int timer = 0;
int counter = 1;

inline int acquire_middle() {
  return n + counter++;
}

void init_sets() {
  for (int i = 1; i < n + counter; ++i) {
    p[i] = i;
    union_rank[i] = 1;
  }
}

int find_set(int x) {
  if (p[x] == x) {
    return x;
  } else {
    return p[x] = find_set(p[x]);
  }
}

void unite_sets(int a, int b) {
  // cout << "unite: " << a << " and " << b << endl;
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (union_rank[a] < union_rank[b]) {
      swap(a, b);
    }
    p[b] = a;
    union_rank[b] += union_rank[a];
  }
}

void bfs_for_components() {
  // bfs queue of pairs of {original start, current vertex to go from};
  queue<int> q;
  for (auto station_id: stations) {
    used[station_id] = 1;
    q.push(station_id);
  }

  while (!q.empty()) {
    int from = q.front();
    // cout << "from: " << from;
    q.pop();

    if (used[from] > k) {
      // cout << " ... not expanding\n";
      continue;
    }
    // cout <<endl;

    for (auto to: g[from]) {
      if (!used[to]) {
        used[to] = used[from] + 1;
        q.push(to);
      }
      unite_sets(from, to);
    }
  }
}

void dfs_for_lca(int v, int p) {
  tin[v] = timer++;
  depth[v] = depth[p] + 1;

  up[v][0] = p;

  for (int j = 1; j < MAXP; ++j) {
    up[v][j] = up[up[v][j - 1]][j - 1];
  }

  for (auto to: g[v]) {
    if (to != p) {
      dfs_for_lca(to, v);
    }
  }
  tout[v] = timer++;
}

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

int distance(int a, int b) {
  return depth[a] + depth[b] - 2 * depth[lca(a, b)];
}

int up_from(int a, int count) {
  // cout << "up " << count << " from " << a << " = ";
  for (int i = MAXP - 1; i >= 0 && count; --i) {
    if ((1 << i) <= count) {
      a = up[a][i];
      count -= (1 << i);
    }
  }
  //cout << a << endl;
  return a;
}

void print_sets() {
  for (int i = 1; i < n + counter; ++i) {
    cout << i << " -- " << find_set(i) << endl;
  }
}

void solve(int a, int b) {
  if (find_set(a) == find_set(b)) {
    // cout << "1. " << find_set(a) << ", " << find_set(b) << endl;
    printf("YES\n");
    return;
  }

  int lca_ab = lca(a, b);
  // cout << "lca(" << a << "," << b << ") is " << lca_ab << endl;
  int a_k_to_b = a;
  int b_k_to_a = b;

  int a_to_lca = distance(a, lca_ab);
  int b_to_lca = distance(b, lca_ab);

  if (a_to_lca + b_to_lca <= 2 * k) {
    printf("YES\n");
    return;
  }

  // cout << "a->lca: " << a_to_lca << ", b->lca: " << b_to_lca << endl;

  if (a_to_lca >= k) {
    a_k_to_b = up_from(a, k);
  } else {
    a_k_to_b = up_from(b, b_to_lca - (k - a_to_lca));
  }

  if (b_to_lca >= k) {
    b_k_to_a = up_from(b, k);
  } else {
    b_k_to_a = up_from(a, a_to_lca - (k - b_to_lca));
  }

  if (find_set(b_k_to_a) == find_set(a_k_to_b)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
}

int main() {
  scanf("%d%d%d", &n, &k, &r);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    int mid = acquire_middle();
    g[from].push_back(mid);
    g[mid].push_back(from);

    g[mid].push_back(to);
    g[to].push_back(mid);

    // cout << from << "->" << mid << "->" << to << endl;
  }

  for (int i = 0; i < r; ++i) {
    int station_id;
    scanf("%d", &station_id);
    stations.push_back(station_id);
    is_station[station_id] = true;
  }

  init_sets();
  bfs_for_components();
  dfs_for_lca(1, 1);
  //print_sets();

  int cnt;
  scanf("%d", &cnt);
  for (int i = 0; i < cnt; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    solve(from, to);
  }
  return 0;
}
