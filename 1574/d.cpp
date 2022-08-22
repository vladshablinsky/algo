#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int result = 0;
vector<int> best_build;
set<vector<int>> st;
vector<vector<int>> v;

int build_cost(const vector<int>& build) {
  int ans = 0;
  for (int i = 0; i < build.size(); ++i) {
    ans += v[i][build[i]];
  }
  return ans;
}

void print_build(const vector<int>& build) {
  for (auto el: build) {
    printf("%d ", el + 1);
  }
  printf("\n");
}

void rec(vector<int>& build, int idx) {
  //print_build(build);
  // subject to ans
  if (!st.count(build)) {
    // cout << "NO\n";
    int cost = build_cost(build);
    if (cost > result) {
      result = cost;
      best_build = build;
    }
  } else {
    // fix this one and move the others
    if (idx + 1 < build.size()) {
      rec(build, idx + 1);
    }

    if (build[idx]) {
      --build[idx];
      rec(build, idx);
      ++build[idx];
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  v.resize(n);
  for (int i = 0; i < n; ++i) {
    int cnt;
    scanf("%d", &cnt);
    v[i].resize(cnt);
    for (int j = 0; j < cnt; ++j) {
      scanf("%d", &v[i][j]);
    }
  }

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    vector<int> cur_build(n);
    for (auto& el: cur_build) {
      scanf("%d", &el);
      --el;
    }
    st.insert(cur_build);
  }

  vector<int> init_build(n);
  for (int i = 0; i < n; ++i) {
    init_build[i] = v[i].size() - 1;
  }

  //cout << "ok\n";

  rec(init_build, 0);
  print_build(best_build);
}
