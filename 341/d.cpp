#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 3005;
const int INF = 1e9;

vector<int> g_direct[MAX_N];
vector<int> g_indirect[MAX_N];

int dist[MAX_N][MAX_N];
int dist_indir[MAX_N][MAX_N];
bool used[MAX_N];
vector<pair<int, int> > farest_direct[MAX_N];
vector<pair<int, int> > farest_indirect[MAX_N];

void init_used() {
  for (int i = 0; i < MAX_N; ++i) {
    used[i] = false;
  }
}

void init_dists() {
  for (int i = 0; i < MAX_N; ++i) {
    for (int j = 0; j < MAX_N; ++j) {
      dist[i][j] = -INF;
      dist_indir[i][j] = -INF;
    }
  }
}

void bfs_direct(int starting) {
  queue<int> q;
  q.push(starting);
  used[starting] = true;
  dist[starting][starting] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < g_direct[v].size(); ++i) {
      int to = g_direct[v][i];
      if (!used[to]) {
        dist[starting][to] = dist[starting][v] + 1;
        used[to] = true;
        q.push(to);
        farest_direct[starting].push_back(make_pair(dist[starting][to], to));
      }
    }
  }
  sort(farest_direct[starting].begin(), farest_direct[starting].end());
}

void bfs_indirect(int starting) {
  queue<int> q;
  q.push(starting);
  used[starting] = true;
  dist_indir[starting][starting] = 0;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < g_indirect[v].size(); ++i) {
      int to = g_indirect[v][i];
      if (!used[to]) {
        dist_indir[starting][to] = dist_indir[starting][v] + 1;
        used[to] = true;
        q.push(to);
        farest_indirect[starting].push_back(make_pair(dist_indir[starting][to], to));
      }
    }
  }
  sort(farest_indirect[starting].begin(), farest_indirect[starting].end());
  //if (starting == 0) {
    //cout << " INDIRECT DISTANCES FROM 0\n";
    //for (int i = 0; i < farest_indirect[starting].size(); ++i) {
      //cout << farest_indirect[starting][i].first << " " << farest_indirect[starting][i].second << endl;
    //}
  //}
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g_direct[u].push_back(v);
    g_indirect[v].push_back(u);
  }

  init_dists();

  for (int i = 0; i < n; ++i) {
    init_used();
    bfs_direct(i);
    init_used();
    bfs_indirect(i);
  }

  //cout << "DONE\n";

  //for (int i = 0; i < n; ++i) {
    //for (int j = 0; j < n; ++j) {
      //if (dist[i][j] > 0) {
        //cout << " dist from " << i << " to " << j << " is " << dist[i][j] << endl;
      //}
    //}
  //}

  int ans = 0;
  int a, b, c, d;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      for (int first = 0; first < 3; ++first) {
        for (int last = 0; last < 3; ++last) {
          if ((int)farest_indirect[i].size() - first - 1 < 0 ||
              (int)farest_direct[j].size() - last - 1 < 0) {
            continue;
          }
          int aa = farest_indirect[i][(int)farest_indirect[i].size() - first - 1].second;
          int dist_a_i = farest_indirect[i][(int)farest_indirect[i].size() - first - 1].first;
          int dd = farest_direct[j][(int)farest_direct[j].size() - last - 1].second;
          int dist_j_d = farest_direct[j][(int)farest_direct[j].size() - last - 1].first;
          if (aa == dd || i == aa || i == dd || j == aa || j == dd) {
            continue;
          }
          int curdist = dist_a_i + dist_j_d + dist[i][j];
          if (curdist > ans) {
            //cout << " a is " << aa << endl;
            //cout << " b is " << i << endl;
            //cout << " c is " << j << endl;
            //cout << " d is " << dd << endl;
            //cout << " distance from a to b " << dist_a_i << endl;
            //cout << " distance from b to c " << dist[i][j] << endl;
            //cout << " distance from c to d " << dist_j_d << endl;
            //cout << " ans is " << curdist << endl;
            ans = curdist;
            a = aa;
            b = i;
            c = j;
            d = dd;
          }
        }
      }
    }
  }

  //cout << ans << endl;
  printf("%d %d %d %d\n", a+1, b+1, c+1 ,d+1);
  return 0;
}
