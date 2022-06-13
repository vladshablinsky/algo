#include <iostream>
#include <vector>

using namespace std;

constexpr int kMaxN = 1000;

int t[kMaxN];
int a[kMaxN];

void build(int v, int tl, int tr) {
  if (tl == tr) {
    t[v] = a[tl];
    return;
  }

  int tm = (tl + tr) / 2;
  build(v * 2, tl, tm);
  build(v * 2 + 1, tm + 1, tr);
  t[v] = t[v * 2] + t[v * 2 + 1];
}

void update(int v, int tl, int tr, int pos, int val) {
  if (tl == tr) {
    t[v] = val;
    return;
  }
  int tm = (tl + tr) / 2;
  if (pos <= tm) {
    update(v * 2, tl, tm, pos, val);
  } else {
    update(v * 2 + 1, tm + 1, tr, pos, val);
  }
  t[v] = t[v * 2] + t[v * 2 + 1];
}

int sum(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }
  if (tl == l && tr == r) {
    return t[v];
  }

  int tm = (tl + tr) / 2;
  return sum(v * 2, tl, tm, l, min(tm, r)) + sum(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
}

int main() {
  int cnt = 20;
  for (int i = 0; i < cnt; ++i) {
    a[i] = i + 1;
  }
  build(1, 0, cnt);
  for (int i = 0; i < cnt; ++i) {
    cout << sum(1, 0, kMaxN, 0, i) << " ";
  }
  for (int i = 0; i < cnt; ++i) {
    update(1, 0, kMaxN, i, 0);
  }
  cout << endl;
  for (int i = 0; i < cnt; ++i) {
    cout << sum(1, 0, kMaxN, i, i) << " ";
  }
  cout << endl;
}


