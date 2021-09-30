#include <iostream>

using namespace std;

const int MAXN = 1000000;
int t[MAXN * 4];
int a[MAXN];

void init(int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
  } else {
    int tm = (tl + tr) / 2;
    init(v * 2, tl, tm);
    init(v * 2 + 1, tm + 1, tr);
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}

int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }
  if (tl == r && tr == r) {
    return t[v];
  }
  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, min(tm, r)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

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

int main() {
  for (int i = 0; i < 10; ++i) {
    a[i] = i + 1;
  }
  init(1, 0, 10);
  for (int i = 0; i < 10; ++i) {
    cout << sum(1, 0, 10, 0, i) << endl;
  }
}
