#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kMaxN = 200005;
constexpr int kInf = 1000000000;
int a[kMaxN];
int t[4 * kMaxN];

void build(int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    t[v] = max(t[v * 2], t[v * 2 + 1]);
  }
}

int get_max(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }
  if (tl == l && tr == r) {
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return max(get_max(v * 2, tl, tm, l, min(r, tm)),
        get_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

bool query(int n, int m) {
  int xs, ys, xf, yf, k;
  scanf("%d%d%d%d%d", &xs, &ys, &xf, &yf, &k);

  if (xs > xf) {
    swap(xs, xf);
  }
  if (ys > yf) {
    swap(yf, ys);
  }

  if ((xf - xs) % k) {
    return false;
  }
  if ((yf - ys) % k) {
    return false;
  }

  // go up as much as we can, then we go down
  int mx = xs + ((n - xs) / k) * k;
  //cout << "mx1: " << mx << endl;
  //cout << "mx2: " << ys - 1 << " " << yf - 1 << " " << get_max(1, 0, n - 1, ys - 1, yf - 1) << endl;
  return get_max(1, 0, m - 1, ys - 1, yf - 1) < mx;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &a[i]);
  }
  build(1, 0, m - 1);

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    if (query(n, m)) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
