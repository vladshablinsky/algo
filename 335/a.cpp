#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MAX_N = 405;

bool used[405];
bool g[MAX_N][MAX_N];
int d[MAX_N];
bool bus_faster;
int n, m;

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a][b] = true;
    g[b][a] = true;
  }

  bus_faster = !g[0][n - 1];
  used[0] = true;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < n; ++i) {
      if (!(bus_faster ^ g[v][i]) && !used[i]) {
        used[i] = true;
        d[i] = d[v] + 1;
        q.push(i);
      }
    }
  }

  if (d[n - 1]) {
    cout << d[n - 1] << "\n";
  } else {
    cout << "-1\n";
  }
  return 0;
}
