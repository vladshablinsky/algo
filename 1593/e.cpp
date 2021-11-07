#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 400005;

int deg[MAXN];
vector<int> g[MAXN];

void init(int n) {
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    deg[i] = 0;
  }
}

int solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  init(n);

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);

    deg[from]++;
    deg[to]++;
  }

  set<pair<int, int>> dv_pairs;
  for (int i = 0; i < n; ++i) {
    dv_pairs.insert({deg[i], i});
    // cout << "add: " << i << ", deg: " << deg[i] << endl;
  }

  for (int i = 0; i < k && dv_pairs.size(); ++i) {
    // cout << "i: " << i << endl;
    vector<int> pending_removes;

    auto it = dv_pairs.begin();
    while (it != dv_pairs.end() && it->first <= 1) {
      pending_removes.push_back(it->second);
      ++it;
    }

    map<int, int> cnts;
    for (auto v: pending_removes) {
      dv_pairs.erase({deg[v], v});
      // cout << "erase: " << v << endl;

      for (auto to: g[v]) {
        if (deg[to] <= 0) {
          continue;
        }
        cnts[to]++;
        dv_pairs.erase({deg[to], to});
        // cout << "erase: " << to << endl;
        // cout << "cnt: " << to << " " << cnts[to] << endl;
        deg[v]--;
        deg[to]--;
        if (deg[to] > 0 || cnts[to] > 1) {
          dv_pairs.insert({deg[to], to});
          // cout << "update: " << to << " " << deg[to] << endl;
        }
      }
    }
  }

  return dv_pairs.size();
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    printf("%d\n", solve());
  }
}
