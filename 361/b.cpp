#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 1e6 + 6;
const int INF = 1e9;

int d[MAX_N];
bool used[MAX_N];
int n;

vector<int> g[MAX_N];
queue<int> q;

void prepare() {
  for (int i = 0; i < n - 1; ++i) {
    g[i].push_back(i + 1);
    g[i + 1].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    d[i] = INF;
  }
}

int main() {
  scanf("%d", &n);
  prepare();
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    --t;
    if (t != i && t != i + 1) {
      g[i].push_back(t);
    }
  }

  used[0] = true;
  d[0] = 0;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int i = 0; i < g[v].size(); ++i) {
      int to = g[v][i];
      if (!used[to]) {
        used[to] = true;
        q.push(to);
        d[to] = d[v] + 1;
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    printf("%d ", d[i]);
  }
  printf("\n");

  return 0;
}

