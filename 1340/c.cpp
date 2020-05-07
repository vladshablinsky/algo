#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

using namespace std;

const int MAXM = 10005;
const int MAXG = 1001;
const int INF = 1e9;

int d[MAXM][MAXG];
int v[MAXM];

void init(int m, int g) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= g; ++j) {
      d[i][j] = INF;
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &v[i]);
  }
  sort(v, v + m);

  int g, r;
  scanf("%d%d", &g, &r);
  init(m, g);

  // 0-1 graph
  deque<pair<int, int>> q;
  q.push_front({0, g});
  d[0][g] = 0;
  while (!q.empty()) {
    int from = q.front().first;
    int g_remain = q.front().second;
    int cost = (g_remain == 0);
    q.pop_front();

    //cout << "now in " << from << "( " << v[from] << " ), " << g_remain << ", d=" << d[from][g_remain] << endl;

    int to = from + 1;
    int len;
    if (to < m && (len = abs(v[from] - v[to])) <= g_remain + cost * g) {
      if (d[from][g_remain] + cost < d[to][g_remain + cost * g - len]) {
        d[to][g_remain + cost * g - len] = d[from][g_remain] + cost;
        if (cost) {
          q.push_back({to, g - len});
        } else {
          q.push_front({to, g_remain - len});
        }
      }
    }
    to = from - 1;
    if (to >= 0 && (len = abs(v[from] - v[to])) <= g_remain + cost * g) {
      if (d[from][g_remain] + cost < d[to][g_remain + cost * g - len]) {
        d[to][g_remain + cost * g - len] = d[from][g_remain] + cost;
        if (cost) {
          q.push_back({to, g - len});
        } else {
          q.push_front({to, g_remain - len});
        }
      }
    }
  }

  int ans = INF;
  for (int j = 0; j <= g; ++j) {
    if (d[m - 1][j] == INF) {
      continue;
    }
    ans = min(ans, (d[m - 1][j]) * (r + g) + g - j);
  }
  if (ans == INF) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}
