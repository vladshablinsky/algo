#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

void process(vector<int>& v, vector<pair<int, int>> &ans, int off) {
  int mn = INF;
  int idx = off;
  for (int i = off; i < v.size(); ++i) {
    if (v[i] < mn) {
      idx = i;
      mn = v[i];
    }
  }
  if (idx != off) {
    v.insert(v.begin() + idx + 1, v.begin() + off, v.begin() + idx);
    v.erase(v.begin() + off, v.begin() + idx);
    ans.push_back({off, idx});
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (auto& el: v) {
    scanf("%d", &el);
  }

  vector<pair<int, int>> ans;
  for (int i = 0; i < n; ++i) {
    process(v, ans, i);
  }

  printf("%d\n", ans.size());
  for (auto [f, s]: ans) {
    printf("%d %d %d\n", f + 1, s + 1, s - f);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
