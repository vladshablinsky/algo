#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 500005;
const long long INF = 1000000000 * 1ll * 1000000000;

struct tree_node {
  long long val;
  long long to_push;
  tree_node(): val(INF), to_push(0) {};
  tree_node(long long val): val(val) {};
} t[4 * MAXN];

int a[MAXN];
int b[MAXN];
int p[MAXN];

void push(int v, int tl, int tr) {
  t[v].val += t[v].to_push;
  if (tl != tr) {
    t[v * 2].to_push += t[v].to_push;
    t[v * 2 + 1].to_push += t[v].to_push;
  }
  t[v].to_push = 0;
}

long long get(int v, int tl, int tr, int pos) {
  push(v, tl, tr);
  if (tl == tr) {
    return t[v].val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      return get(v * 2, tl, tm, pos);
    } else {
      return get(v * 2 + 1, tm + 1, tr, pos);
    }
  }
}

void upd(int v, int tl, int tr, int pos, long long val) {
  push(v, tl, tr);
  if (tl == tr) {
    t[v].val = val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      upd(v * 2, tl, tm, pos, val);
    } else {
      upd(v * 2 + 1, tm + 1, tr, pos, val);
    }
  }
}

void add(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) {
    return;
  }

  if (tl == l && tr == r) {
    t[v].to_push += val;
  } else {
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    add(v * 2, tl, tm, l, min(r, tm), val);
    add(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
  }
}

int main() {
  int n, m;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
  }

  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &b[i]);
  }

  upd(1, 0, m, 0, 0);
  for (int i = 0; i < n; ++i) {
    int cnt_less = lower_bound(b, b + m, a[i]) - b;
    bool a_i_in_b = (cnt_less < m && b[cnt_less] == a[i]);
    long long cost_without_a_i = get(1, 0, m, cnt_less);
    if (p[i] < 0) {
      add(1, 0, m, 0, m, p[i]);
    } else {
      add(1, 0, m, 0, cnt_less, p[i]);
    }

    if (a_i_in_b && get(1, 0, m, cnt_less + 1) > cost_without_a_i) {
      upd(1, 0, m, cnt_less + 1, cost_without_a_i);
    }
  }

  long long ans = get(1, 0, m, m);
  if (ans > MAXN * 1ll * 1000000000) {
    cout << "NO\n";
  } else {
    cout << "YES\n" << ans << "\n";
  }

  return 0;
}
