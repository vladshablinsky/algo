#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kMaxN = 1005;
constexpr int kMaxOps = 13;
constexpr int kInf = 1000000000;

int cnt_ops[kMaxN];
int f[kMaxN][kMaxOps * kMaxN];

void init_cnt_ops() {
  int sum = 1;
  int ops = 0;

  cnt_ops[1] = 0;

  for (int i = 2; i < kMaxN; ++i) {
    cnt_ops[i] = kInf;
  }

  int res = 0;
  for (int i = 1; i < kMaxN; ++i) {
    for (int x = 1; x < kMaxN; ++x) {
      int add = i / x;
      if (i + add < kMaxN) {
        cnt_ops[i + add] = min(cnt_ops[i + add], cnt_ops[i] + 1);
      }
    }
    res = max(res, cnt_ops[i]);
  }
}

void init_f(int n) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= kMaxOps * n; ++j) {
      f[i][j] = -kInf;
    }
  }
  f[0][0] = 0;
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  vector<int> weight(n), c(n);
  for (auto& el: weight) {
    scanf("%d", &el);
    el = cnt_ops[el];
  }
  for (auto& el: c) {
    scanf("%d", &el);
  }

  // f[i][j] using first i items what is the max cost with weight j
  init_f(n);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= min(k, kMaxOps * n); ++j) {
      if (j - weight[i - 1] >= 0) {
        f[i][j] = max(f[i - 1][j], f[i - 1][j - weight[i - 1]] + c[i - 1]);
      } else {
        f[i][j] = f[i - 1][j];
      }

      ans = max(ans, f[i][j]);
    }
  }
  printf("%d\n", ans);
}

int main() {
  init_cnt_ops();

  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}


