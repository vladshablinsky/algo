#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const long long INF = 1000000000 * 1ll * 1000000000;
struct node {
  long long val; // min while sons not yet recalculated.
  long long to_add;
  bool to_push;
} t[4 * MAXN];

pair<int, int> a[MAXN];

// min / add ops
//
void push(int v) {
  if (t[v].to_push) {
    t[v].val += t[v].to_add;
    if (v * 2 < 4 * MAXN) {
      t[v * 2].to_push = true;
      t[v * 2].to_add += t[v].to_add;
    }
    if (v * 2 + 1 < 4 * MAXN) {
      t[v * 2 + 1].to_push = true;
      t[v * 2 + 1].to_add += t[v].to_add;
    }
    t[v].to_add = 0;
    t[v].to_push = false;
  }
}

void add(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) {
    return;
  }
  if (tl == l && tr == r) {
    t[v].to_push = true;
    t[v].to_add += val;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    add(v * 2, tl, tm, l, min(tm, r), val);
    add(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val);
    t[v].val = min(t[v * 2].val + t[v * 2].to_add, t[v * 2 + 1].val + t[v * 2 + 1].to_add);
  }
}

long long query_min(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return INF;
  }

  if (tl == l && tr == r) {
    return t[v].val + t[v].to_add;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    return min(query_min(v * 2, tl, tm, l, min(tm, r)),
        query_min(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i].first);
    a[i].second = i;
  }
  sort(a, a + n, std::greater<pair<int, int>>());

  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    auto [c, idx] = a[i];
    auto res = query_min(1, 0, n - 1, idx, n - 1);
    // cout << "try to add " << c << " at "<< idx << ", res: " << res << endl;
    if (res + c >= 0) {
      ++cnt;
      add(1, 0, n - 1, idx, n - 1, c);
    }
  }

  cout << cnt << "\n";
}
