#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 2e5 + 5;

pair<int, int> t[4 * MAXN];
int n, k;
int a, b;
int q;

void update(int v, int tl, int tr, int pos, int delta) {
  if (tl == tr) {
    if (t[v].first + delta <= b) {
      t[v].first += delta;
    } else {
      t[v].first = b;
    }

    if (t[v].second + delta <= a) {
      t[v].second += delta;
    } else {
      t[v].second = a;
    }
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(v * 2, tl, tm, pos, delta);
    } else {
      update(v * 2 + 1, tm + 1, tr, pos, delta);
    }
    t[v].first = t[v * 2].first + t[v * 2 + 1].first;
    t[v].second = t[v * 2].second + t[v * 2 + 1].second;
  }
}

pair<int, int> sum(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return make_pair(0, 0);
  } else if (l == tl && r == tr) {
    return t[v];
  } else {
    int tm = (tl + tr) / 2;
    pair<int, int> l_sum = sum(v * 2, tl, tm, l, min(r, tm));
    pair<int, int> r_sum = sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    return make_pair(l_sum.first + r_sum.first, l_sum.second + r_sum.second);
  }
}

int main() {
  scanf("%d%d%d%d%d", &n, &k, &a, &b, &q);
  for (int i = 0; i < q; ++i) {
    int q_id;
    scanf("%d", &q_id);
    if (q_id == 1) {
      int d_i, a_i;
      scanf("%d%d", &d_i, &a_i);
      update(1, 0, n, d_i, a_i);
    } else {
      int p_i;
      scanf("%d", &p_i);
      printf("%d\n", sum(1, 0, n, 0, p_i - 1).first +
          sum(1, 0, n, p_i + k, n).second);
    }
  }
  return 0;
}
