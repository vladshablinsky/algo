#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
const long long INF = 1000000000 * 1ll * 1000000000;
int a[MAXN];
int cost_i[MAXN];

// c[i] is a cost to have {1, ... i}|{i + 1, ... n} if we split
// c[0] is {}|{1 ... n}, and c[n] is {1...n}|{}
// after first element
long long c[MAXN];

struct node {
  long long val;
  long long to_add;
  bool needs_push;
} t[MAXN * 4];

void init(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].val = c[tl];
  } else {
    int tm = (tl + tr) / 2;
    init(v * 2, tl, tm);
    init(v * 2 + 1, tm + 1, tr);
    t[v].val = min(t[v * 2].val, t[v * 2 + 1].val);
  }
}

void push(int v) {
  if (!t[v].needs_push) {
    return;
  } else {
    if (v * 2 + 1 < MAXN * 4) {
      t[v * 2].needs_push = true;
      t[v * 2].to_add += t[v].to_add;
      t[v * 2 + 1].needs_push = true;
      t[v * 2 + 1].to_add += t[v].to_add;
    }
    t[v].val += t[v].to_add;
    t[v].to_add = 0;
    t[v].needs_push = false;
  }
}

void add(int v, int tl, int tr, int l, int r, int val) {
  if (l > r) {
    return;
  }

  if (tl == l && tr == r) {
    t[v].to_add += val;
    t[v].needs_push = true;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    add(v * 2, tl, tm, l, min(tm, r), val);
    add(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val);

    // update after children are recalculated!
    t[v].val = min(t[v * 2].val + t[v * 2].to_add, t[v * 2 + 1].val + t[v * 2 + 1].to_add);
  }
}

long long query(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return INF;
  }
  if (tl == l && tr == r) {
    return t[v].val + t[v].to_add;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    return min(query(v * 2, tl, tm, l, min(tm, r)), query(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &cost_i[a[i]]);
  }

  // suppose we split before the first element just for initialization
  for (int i = 1; i <= n; ++i) {
    c[i] = c[i - 1] + cost_i[i];
  }
  init(1, 0, n);


  auto print = [n](){
    cout << "res: ";
    for (int i = 0; i <= n; ++i) {
      cout << query(1, 0, n, i, i) << " ";
    }
    cout << endl;
  };

  // split after element i
  long long result = INF;
  for (int i = 1; i < n; ++i) {
    int x = a[i - 1];

    // on this iteration x is on the left initially
    // we need to move it to the right
    // for {}, {1}, {1, 2} ... {1 ... x-1} left-sets
    add(1, 0, n, 0, x - 1, cost_i[x]);
    // we need not to move it to the left
    // for {1 ... x}, {1...x+1} ... {1, n} left-sets
    add(1, 0, n, x, n, -cost_i[x]);
    result = min(result, query(1, 0, n, 0, n));
  }

  cout << result << "\n";
  return 0;
}
