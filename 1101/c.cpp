#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

const int MAXN = 200005;
vector<pair<pair<int, int>, int>> v;
int ans[MAXN];

void solve() {
  v.clear();
  int n;
  scanf("%d", &n);
  fill(ans, ans + n, 0);
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    v.push_back({make_pair(l, r), i});
  }
  sort(v.begin(), v.end());
  int i;
  int cur_max_right = v[0].first.second;
  for (i = 0; i < n; ++i) {
    if (cur_max_right < v[i].first.first) {
      break;
    } else {
      cur_max_right = max(cur_max_right, v[i].first.second);
      ans[v[i].second] = 1;
    }
  }

  if (i == n) {
    cout << "-1\n";
  } else {
    for (int j = 0; j < n; ++j) {
      cout << ans[j] + 1 << " ";
    }
    cout << "\n";
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
