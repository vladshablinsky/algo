#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 3000005;

int a[2 * MAXN];
int max_pos[MAXN];
int min_pos[MAXN];
int prev_idx[MAXN];

int t[8 * MAXN];

void update(int v, int tl, int tr, int pos, int val) {
  if (tl == tr) {
    t[v] = val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(v * 2, tl, tm, pos, val);
    } else {
      update(v * 2 + 1, tm + 1, tr, pos, val);
    }
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}

int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }
  if (tl == l && tr == r) {
    return t[v];
  } else {
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm)) +
      sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    update(1, 0, n + m, i, 1);
    prev_idx[n - i] = i;
  }

  int cur_id;
  for (int i = n; i < n + m; ++i) {
    scanf("%d", &cur_id);
    min_pos[cur_id] = 1;
    max_pos[cur_id] = max(max_pos[cur_id], sum(1, 0, n + m, prev_idx[cur_id] + 1, i));
    update(1, 0, n + m, prev_idx[cur_id], 0);
    update(1, 0, n + m, i, 1);
    prev_idx[cur_id] = i;
  }

  for (int i = 1; i <= n; ++i) {
    max_pos[i] = max(max_pos[i], sum(1, 0, n + m, prev_idx[i] + 1, n + m - 1));
  }

  for (int i = 1; i <= n; ++i) {
    printf("%d %d\n", (min_pos[i] ? 1: i), 1 + max_pos[i]);
  }
  return 0;
}
