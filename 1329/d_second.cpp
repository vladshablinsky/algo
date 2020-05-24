#include <iostream>
#include <cstdio>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int INF = 1000000000;
string s;
int n;
vector<int> g[MAXN];

void init() {
  for (int i = 0; i < n; ++i) {
    g[i].clear();
  }
}

void solve() {
  cin >> s;
  n = s.length();
  vector<pair<int, int>> segments;

  char prev_char = s[0];
  for (int i = 0; i < n; ++i) {
    if (s[i] == prev_char) {
      segments.emplace_back(i, i);
    } else {
      segments.back().second = i;
    }
    prev_char = s[i];
  }

  // now iterate segments and build DAG.
  vector<int> hanging; // hanging segments always have same ending value.
  int prev_from = -1;
  int m = segments.size();
  for (int to = 0; to < m; ++to) {
    if (!hanging.empty()) {
      char symbol_to_link = s[segments[hanging.back()].second];
      if (s[segments[to].first] != symbol_to_link) {
        for (auto from: hanging) {
          g[to].push_back(from);
          cout << "add edge: (" << from << ", " << to << ")\n";
        }
        hanging.clear();
      }
    }

    if (prev_from != -1) {
      hanging.push_back(prev_from);
    }
    prev_from = to;
  }

  vector<int> f(m, INF);
  vector<int> p(m, -1);
  f[0] = 1;
  for (int i = 1; i < m; ++i) {
    f[i] = f[i - 1] + 1;
    p[i] = i - 1;
    for (int from: g[i]) {
      if (f[from] + (i - from - 1) < f[i]) {
        f[i] = f[from] + (i - from - 1);
        p[i] = from;
      }
    }
  }

  cout << f[m - 1] << "\n";
  vector<pair<int, int>> ans;
  pair<int, int> cur_path = segments[m - 1]; // path with segments we want to delete at once
  int cnt_removed_for_path = 0; // number of removed segments while building cur_path
  int idx = m - 1;
  while (p[idx] != -1) {
    if (p[idx] == idx - 1) { // cur_path is broken
      ans.push_back({cur_path.first, cur_path.second - cnt_removed_for_path});
      cur_path = segments[idx - 1];
      cnt_removed_for_path = 0;
    } else { // extend cur_path, but remove in-betweens one by one
      for (int remove_idx = idx - 1; remove_idx > p[idx]; --remove_idx) {
        ans.push_back({segments[remove_idx].first, segments[remove_idx].second});
        cnt_removed_for_path += (segments[remove_idx].second - segments[remove_idx].first + 1);
      }
      cur_path.first = segments[p[idx]].first;
    }
    idx = p[idx];
  }
  // add last path
  ans.push_back({cur_path.first, cur_path.second - cnt_removed_for_path});

  printf("%d\n", int(ans.size()));
  for (auto el: ans) {
    printf("%d %d\n", el.first + 1, el.second + 1);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }

  return 0;
}
