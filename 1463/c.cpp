#include <iostream>

using namespace std;

const int MAXN = 100005;
const long long INF = 1000000005 * 1ll * 1000000005;
long long t[MAXN];
int x[MAXN];

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld %d", &t[i], &x[i]);
  }
  t[n] = INF;

  long long prev_time_start = t[0];
  long long from = 0;
  long long vel = x[0] > 0 ? 1 : -1;
  long long tm = abs(x[0]);
  int cnt_succ = 0;

  for (int i = 1; i <= n; ++i) {
    long long pos_cur = from + vel * min(tm, t[i] - prev_time_start);
    long long pos_prev = from + vel * min(tm, t[i - 1] - prev_time_start);

    if (x[i - 1] >= min(pos_cur, pos_prev) && x[i - 1] <= max(pos_cur, pos_prev)) {
      ++cnt_succ;
    }

    if (prev_time_start + tm <= t[i]) {
      prev_time_start = t[i];
      tm = abs(x[i] - pos_cur);
      vel = x[i] > pos_cur ? 1 : -1;
      from = pos_cur;
    }
  }

  printf("%d\n", cnt_succ);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
