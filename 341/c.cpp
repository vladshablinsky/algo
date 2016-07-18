#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 1e5 + 5;
int l[MAX_N], r[MAX_N];
int p;
int n;

double prob_div(int idx) {
  double cnt_divisible = (r[idx] / p - (l[idx] - 1) / p);
  double cnt = r[idx] - l[idx] + 1;
  return cnt_divisible / cnt;
}

double prob_not_div(int idx) {
  return 1. - prob_div(idx);
}

int main() {
  scanf("%d%d", &n, &p);

  double ans = 0.;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &l[i], &r[i]);
  }

  for (int i = 0; i < n; ++i) {
    int prev_idx = (i - 1 + n) % n;
    int next_idx = (i + 1) % n;

    ans += 4000. * prob_div(i) * prob_not_div(prev_idx);
    ans += 2000. * prob_div(i) * prob_div(prev_idx);
  }

  printf("%.7lf\n", ans);
  return 0;
}
