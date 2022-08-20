#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kInf = 1000000000;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  vector<pair<int, int>> v(n);
  vector<int> cpy(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i].first);
    v[i].second = i;
    cpy[i] = v[i].first;
  }

  auto get_max_adj = [&](int k) {
    int res = 0;
    if (k + 1 < n) {
      res = max(res, cpy[k + 1]);
    }
    if (k) {
      res = max(res, cpy[k - 1]);
    }
    return res;
  };

  auto cmp_value = [&](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if (lhs.first == rhs.first) {
      return get_max_adj(lhs.second) > get_max_adj(rhs.second);
    }
    return lhs.first < rhs.first;
  };
  auto cmp_order = [](const pair<int,int>& lhs, const pair<int,int>& rhs) {
    return lhs.second < rhs.second;
  };

  auto get_ans = [&]() {
    int mn = kInf;
    int max_adj = 0;
    for (int i = 0; i + 1 < n; ++i) {
      auto cur = std::minmax(v[i].first, v[i + 1].first);
      if (max_adj < cur.first) {
        max_adj = cur.first;
      }

      mn = std::min(cur.first, mn);
    }

    //cout << "for: ";
    //for (int i = 0; i < n; ++i) {
    //  cout << v[i].first << " ";
    //}
    //cout << "\n ans is: min(" << max_adj << ", " << mn + mn <<")\n";

    return min(max_adj, mn + mn);
  };

  sort(v.begin(), v.end(), cmp_value);
  for (int i = 0; i < k; ++i) {
    v[i].first = kInf;
  }

  sort(v.begin(), v.end(), cmp_order);
  auto ans = get_ans();
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    mx = max(mx, cpy[i]);
    v[i].first = cpy[i];
  }
  sort(v.begin(), v.end(), cmp_value);
  for (int i = 0; i < k - 1; ++i) {
    v[i].first = kInf;
    mx = kInf;
  }

  sort(v.begin(), v.end(), cmp_order);
  int min_mx_adj = kInf;
  int min_mx_adj_idx = 0;
  for (int i = 0; i < n; ++i) {
    if (v[i].first == mx) {
      if (i && v[i - 1].first <= min_mx_adj) {
        min_mx_adj = v[i - 1].first;
        min_mx_adj_idx = i - 1;
      }
      if (i + 1 < n && v[i + 1].first <= min_mx_adj) {
        min_mx_adj = v[i + 1].first;
        min_mx_adj_idx = i + 1;
      }
    }
  }
  v[min_mx_adj_idx].first = kInf;
  ans = max(ans, get_ans());

  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
