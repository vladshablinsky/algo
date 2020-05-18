#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdint>

using namespace std;

const int MAXN = 1000001;
const int INF = 1e9;

struct storage {
  uint8_t lsb;
  uint8_t csb;
  uint8_t msb;

  storage(): lsb(0), csb(0), msb(0) {};

  int get_value() {
    return (1 << 16) * msb + (1 << 8) * csb + lsb;
  }

  void set_value(int x) {
    lsb = x & ((1 << 8) - 1);
    csb = (x >> 8) & ((1 << 8) - 1);
    msb = x >> 16;
  }
};

storage t[MAXN + 5];

int sum(int r) {
  int ans = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) {
    ans += t[r].get_value();
  }
  return ans;
}

void inc(int i, int delta) {
  for (; i < MAXN; i = (i | (i + 1))) {
    t[i].set_value(t[i].get_value() + delta);
  }
}

int get_kth(int k) {
  int l = 0;
  int r = MAXN;

  int ans = INF;
  while (l <= r) {
    int m = (l + r) / 2;
    if (sum(m) >= k) {
      ans = min(m, ans);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  return ans;
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  int prev = 0;
  int cur;
  int cur_cnt = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &cur);
    if (prev == cur || !prev) {
      ++cur_cnt;
    } else {
      inc(prev, cur_cnt);
      cur_cnt = 1;
    }
    prev = cur;
  }

  int k;
  for (int i = 0; i < q; ++i) {
    scanf("%d", &k);
    if (k < 0) {
      inc(get_kth(-k), -1);
    } else {
      inc(k, 1);
    }
  }

  if ((k = get_kth(1)) == INF) {
    printf("0\n");
  } else {
    printf("%d\n", k);
  }
  return 0;
}
