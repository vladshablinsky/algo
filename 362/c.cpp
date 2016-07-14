#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 1005;
int cur_p = 0;

struct Query {
  long long v, u;
  long long lca;
  int w;
  Query(): v(0), u(0), w(0) {};
  Query(long long v, long long u, int w): v(v), u(u), w(w) {};
};

Query segs[MAXN];

long long lca(long long v, long long u) {
  while (u != v) {
    if (u < v) {
      v >>= 1;
    } else {
      u >>= 1;
    }
  }
  return u;
}

// intersect first with second
int intersect(long long v_1, long long x_1, long long v_2, long long x_2) {
  int ans = 0;

  if (v_1 & v2)

  while (v_1 != v_2 && (v_1 != x_1 || v_2 != x_2)) {
    if (v_1 < v_2) {
      v_2 >>= 1;
    } else {
      v_1 >>= 1;
    }
  }

  while (v_1 != x_1 && v_2 != x_2) {
    v_1 >>= 1;
    v_2 >>= 1;
    ++ans;
  }
  return ans;
}

int query(long long u, long long v) {
  long long x = lca(u, v);
  int ans = 0;
  for (int i = 0; i < cur_p; ++i) {
    ans += intersect(u, x, segs[i].u, segs[i].lca) * segs[i].w;
    ans += intersect(u, x, segs[i].v, segs[i].lca) * segs[i].w;
    ans += intersect(v, x, segs[i].u, segs[i].lca) * segs[i].w;
    ans += intersect(v, x, segs[i].v, segs[i].lca) * segs[i].w;
  }
  return ans;
}

int main() {
  int q;
  long long v, u;
  int w;

  scanf("%d", &q);

  for (int i = 0; i < q; ++i) {
    int type;
    scanf("%d", &type);
    if (type == 1) {
      cin >> v >> u >> w;
      segs[cur_p] = Query(v, u, w);
      segs[cur_p].lca = lca(v, u);
      cur_p++;
    } else {
      cin >> v >> u;
      printf("%d\n", query(v, u));
    }
  }
  return 0;
}
