#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool check(const vector<pair<int, int>> &v, int n, int m, bool output=false) {
  if (n * 1ll * n - (n / 2) * 1ll * (n / 2) < m) {
    return false;
  }


  vector<vector<int>> ans;
  ans.resize(n);
  for (int i = 0; i < n; ++i) {
    ans[i] = vector<int>(n, 0);
  }

  // Must be sure there is no realocations in ans!
  vector<int*> a;
  for (int i = 0; i < n; i += 2) {
    for (int j = 1; j < n; j += 2) {
      a.push_back(&ans[i][j]);
    }
  }
  vector<int*> b;
  for (int i = 1; i < n; i += 2) {
    for (int j = 0; j < n; j += 2) {
      b.push_back(&ans[i][j]);
    }
  }
  vector<int*> c;
  for (int i = 0; i < n; i += 2) {
    for (int j = 0; j < n; j += 2) {
      c.push_back(&ans[i][j]);
    }
  }

  auto cur_a = a.begin();
  auto cur_b = b.begin();
  auto cur_c = c.begin();

  for (auto [cnt, el]: v) {
    int a_free = a.end() - cur_a;
    int b_free = b.end() - cur_b;
    int c_free = c.end() - cur_c;
    if (int mx = max(a_free, b_free); cnt > mx) {
      if (cnt > mx + c_free) {
        return false;
      }

      if (a_free > b_free) {
        while (cur_a != a.end()) {
          **cur_a = el;
          --cnt;
          ++cur_a;
        }
      } else {
        while (cur_b != b.end()) {
          **cur_b = el;
          --cnt;
          ++cur_b;
        }
      }
      while (cnt) {
        **cur_c = el;
        --cnt;
        ++cur_c;
      }
    } else if (a_free >= cnt) {
      while (cnt) {
        **cur_a = el;
        --cnt;
        ++cur_a;
      }
    } else { // b_free >= cnt
      while (cnt) {
        **cur_b = el;
        --cnt;
        ++cur_b;
      }
    }
  }

  if (output) {
    printf("%d\n", n);
    for (auto& row: ans) {
      for (auto el: row) {
        printf("%d ", el);
      }
      printf("\n");
    }

  }
  return true;
}

void solve() {
  int m, k;
  scanf("%d%d", &m, &k);
  vector<pair<int, int>> v(k);
  for (int i = 0; i < k; ++i) {
    scanf("%d", &v[i].first);
    v[i].second = i + 1;
  }
  sort(v.begin(), v.end(), std::greater<pair<int, int>>());

  int start_n = int(sqrt(4 * m / 3));
  int end_n = int(sqrt(m)) * 2 + 1;
  int min_n = end_n;
  while (start_n <= end_n) {
    int mid_n = (start_n + end_n) / 2;
    if (check(v, mid_n, m)) {
      min_n = min(min_n, mid_n);
      end_n = mid_n - 1;
    } else {
      start_n = mid_n + 1;
    }
  }

  check(v, min_n, m, true);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
