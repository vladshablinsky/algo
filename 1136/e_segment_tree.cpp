#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

const int MAXN = 100005;

long long sum_k[MAXN];
int a[MAXN];

struct node {
  long long sum;
  long long sum_k_i;
  long long max_val;
  long long push_value;
  bool need_push;
  int length;

  node():
    sum(0),
    sum_k_i(0),
    max_val(0),
    need_push(false),
    push_value(0),
    length(0)
  {}

} t[4 * MAXN];

void init_t(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].sum = a[tl] - sum_k[tl];
    t[v].sum_k_i = sum_k[tl];
    t[v].max_val = a[tl] - sum_k[tl];
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    init_t(v * 2, tl, tm);
    init_t(v * 2 + 1, tm + 1, tr);
    t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
    t[v].sum_k_i = t[v * 2].sum_k_i + t[v * 2 + 1].sum_k_i;
    t[v].max_val = std::max(t[v * 2].max_val, t[v * 2 + 1].max_val);
    t[v].length = (tr - tl + 1);
  }
}

void push(int v) {
  //printf("in push %d", v);
  //std::cout << " length: " << t[v].length << ", need_push: " << t[v].need_push << "\n";
  if (t[v].length > 1 && t[v].need_push) {
    //printf("in push met conds%d\n", v);
    t[v * 2].push_value = t[v].push_value;
    t[v * 2].sum = t[v * 2].push_value * t[v * 2].length;
    t[v * 2].max_val = t[v * 2].push_value;
    t[v * 2].need_push = true;

    t[v * 2 + 1].push_value = t[v].push_value;
    t[v * 2 + 1].sum = t[v * 2 + 1].push_value * t[v * 2 + 1].length;
    t[v * 2 + 1].max_val = t[v * 2 + 1].push_value;
    t[v * 2 + 1].need_push = true;
  }
  t[v].need_push = false;
}

long long sum(int v, int tl, int tr, int l, int r) {
  //printf("sum v: %d, tl: %d, tr: %d, l: %d, r: %d\n", v, tl, tr, l, r);

  if (l > r) {
    return 0;
  }

  push(v);
  if (tl == l && tr == r) {
    //printf("RETURNING: %lld\n", t[v].sum + t[v].sum_k_i);
    return t[v].sum + t[v].sum_k_i;
  } else {
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, std::min(tm, r)) + sum(v * 2 + 1, tm + 1, tr, std::max(tm + 1, l), r);
  }
}

int lower_bound(int v, int tl, int tr, int val) {
  //std::cout << "lb " << v << ", " << tl << ", " << tr << ", " << val << "\n";
  //std::cout << t[v].max_val << "\n";
  if (tl == tr) {
    return tl;
  }

  push(v);
  int tm = (tl + tr) / 2;
  if (t[v * 2].max_val >= val) {
    return lower_bound(v * 2, tl, tm, val);
  } else {
    return lower_bound(v * 2 + 1, tm + 1, tr, val);
  }
}

void update(int v, int tl, int tr, int l, int r, long long x) {
  //printf("update v: %d, tl: %d, tr: %d, l: %d, r: %d, x: %lld\n", v, tl, tr, l, r, x);
  if (l > r) {
    return;
  }
  //printf("before update v: %d, tl: %d, tr: %d, x: %lld, sum is %lld\n", v, tl, tr, x, t[v].sum + t[v].sum_k_i);

  if (tl == tr) {
    t[v].sum = x;
    t[v].max_val = x;
    return;
  }

  push(v);
  if (tl == l && tr == r) {
    t[v].sum = x * (r - l + 1);
    t[v].max_val = x;
    t[v].push_value = x;
    t[v].need_push = true;
  } else {
    int tm = (tl + tr) / 2;
    update(v * 2, tl, tm, l, std::min(tm, r), x);
    update(v * 2 + 1, tm + 1, tr, std::max(tm + 1, l), r, x);
    t[v].sum = t[v * 2].sum + t[v * 2 + 1].sum;
    t[v].max_val = std::max(t[v * 2].max_val, t[v * 2 + 1].max_val);
  }

  //printf("after update v: %d, tl: %d, tr: %d, x: %lld, sum is %lld\n", v, tl, tr, x, t[v].sum + t[v].sum_k_i);

}

int main() {
  int n, q;
  std::scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    std::scanf("%d", &a[i]);
  }

  long long cur_sum_k = 0;
  for (int i = 0; i < n - 1; ++i) {
    int k_i;
    std::scanf("%d", &k_i);
    cur_sum_k += k_i;
    sum_k[i + 1] = cur_sum_k;
  }

  // for (int i = 0; i < n; ++i) {
  //   std::cout << a[i] - sum_k[i] << " ";
  // }
  // std::cout << std::endl;

  init_t(1, 0, n - 1);

  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    char c;
    std::cin >> c;
    if (c == '+') {
      int idx, x;
      std::scanf("%d%d", &idx, &x);
      --idx;
      long long cur_b_i = sum(1, 0, n - 1, idx, idx) - sum_k[idx];

      int idx_lb = n;
      //std::cout << "t[1].max_val is " << t[1].max_val << std::endl;
      //std::cout << "cur_b is " << cur_b_i << std::endl;
      if (t[1].max_val >= cur_b_i + x) {
       idx_lb = lower_bound(1, 0, n - 1, cur_b_i + x);
      }

      //std::cout << "idx: " << idx << std::endl;
      //std::cout << "idx_lb: " << idx_lb << std::endl;

      update(1, 0, n - 1, idx, std::max(idx, idx_lb - 1), cur_b_i + x);
    } else {
      int l, r;
      std::scanf("%d%d", &l, &r);
      --l; --r;
      std::cout << sum(1, 0, n - 1, l, r) << "\n";
    }
  }
  return 0;
}
