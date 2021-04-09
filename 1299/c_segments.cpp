#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1000005;
int a[MAXN];
double sum[MAXN];
const double INF = 1e14;
int n;

struct Node {
  double avg;
  int len = 0;
  Node() = default;
  Node(double avg, int len): avg(avg), len(len) {};
} t[4 * MAXN];

void init_sum() {
  sum[0] = a[0];
  for (int i = 1; i < n; ++i) {
    sum[i] = sum[i - 1] + a[i];
  }
}

double get_sum(int l, int r) {
  double ans = sum[r];
  if (l - 1) {
    ans -= sum[l - 1];
  }
  return ans;
}

void init(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].len = 1;
    t[v].avg = a[tl];
    return;
  }

  int tm  = (tl + tr) / 2;
  init(v * 2, tl, tm);
  init(v * 2 + 1, tm + 1, tr);

  auto& tln = t[v * 2];
  auto& trn = t[v * 2 + 1];

  int left_len = (tm - tl + 1);
  t[v].avg = (get_sum(tl, tm) + trn.avg * trn.len) / (left_len + trn.len);
  t[v].len = left_len + trn.len;

  if (tln.avg < t[v].avg) {
    t[v].avg = tln.avg;
    t[v].len = tln.len;
  }
}

Node get_min(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return {INF, 0};
  }

  if (l == tl && r == tr) {
    cout << l << "..." << r << " stored: {" << t[v].len << ", " << t[v].avg << "}\n";
    return t[v];
  }

  int tm = (tl + tr) / 2;
  int left_r = min(r, tm);
  auto left_ans = get_min(v * 2, tl, tm, l, left_r);
  auto right_ans = get_min(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);

  if (!left_ans.len) {
    return right_ans;
  }

  if (!right_ans.len) {
    return left_ans;
  }

  int left_len = (left_r - l + 1);
  Node ans;
  ans.avg = (get_sum(l, left_r) + right_ans.avg * right_ans.len) / (left_len + right_ans.len);
  ans.len = left_len + right_ans.len;

  if (left_ans.avg < ans.avg) {
    ans.avg = left_ans.avg;
    ans.len = left_ans.len;
  }

  cout << l << "..." << r << " calculated: {" << ans.len << ", " << ans.avg << "}\n";

  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  init_sum();
  init(1, 0, n - 1);

   // for (int i = 0; i < n; ++i) {
   //   auto res = get_min(1, 0, n - 1, 0, i);
   //   cout << "min_pref: " << res.avg << ", len: " << res.len << endl;
   // }
   //

  cout << "min 1...9\n";
  auto res = get_min(1, 0, n - 1, 0, 8);
  cout << "min_pref: " << res.avg << ", len: " << res.len << endl;
  return 0;

  int l = 0;
  while (l < n) {
    auto res = get_min(1, 0, n - 1, l, n - 1);
    for (int i = 0; i < res.len; ++i) {
      printf("%.08f ", res.avg);
    }
    l += res.len;
  }

  return 0;
}
