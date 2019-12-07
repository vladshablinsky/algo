#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5005;

vector<int> g[MAXN]; // g[i] = {x_j}, where x_j is a vertex of second part of the graph
vector<bool> used(MAXN);
vector<int> mt(MAXN, -1);

int p[MAXN];
int c[MAXN];
int queries[MAXN];
bool not_in_team[MAXN];

bool try_kuhn(int v) {
  used[v] = true;
  for (auto to: g[v]) {
    if (mt[to] == -1 || (!used[mt[to]] && try_kuhn(mt[to]))) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m, d;
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    c[i]--;
  }

  scanf("%d", &d);
  for (int i = 0; i < d; ++i) {
    scanf("%d", &queries[i]);
    --queries[i];
    not_in_team[queries[i]] = true;
  }

  vector<int> ans;
  // student left after d days:
  for (int i = 0; i < n; ++i) {
    if (!not_in_team[i]) {
      g[p[i]].push_back(c[i]);  // edge from potential to club
    }
  }

  // simulate days from last to first
  int cur_mex = 0;
  for (int i = d - 1; i >= 0; --i) {
    while(try_kuhn(cur_mex)) {
      used.assign(MAXN, false);
      ++cur_mex;
    }
    used.assign(MAXN, false);

    ans.push_back(cur_mex);
    g[p[queries[i]]].push_back(c[queries[i]]);
  }

  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    printf("%d\n", *it);
  }
  return 0;
}
