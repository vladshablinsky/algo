#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1e6 + 5;
const long long INF = 1000000000ll * 1000000000ll;
int a[MAXN];
int a_for_iteration[MAXN];

int main() {
  int n;
  long long sum = 0;
  long long ans = INF;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }

  if (sum == 1) {
    cout << "-1\n";
    return 0;
  }

  auto try_for_divisor = [&](long long divisor) {
    // cout << "try for divisor: " << divisor << endl;
    long long cur_ans = 0;
    int l = 0;
    int r = 0;

    long long left_sum = 0;
    long long left_cnt = 0;

    while (l < n && r < n) {
      if (left_cnt + a_for_iteration[r] < divisor) {
        left_cnt += a_for_iteration[r++];
        left_sum += left_cnt;
      } else {
        long long right_sum = 0;
        long long min_res = left_sum + right_sum;

        long long right_cnt = divisor - left_cnt;
        right_sum += right_cnt;
        a_for_iteration[r] -= right_cnt;

        for (int j = r - 1; j >= l; --j) {
          left_sum -= left_cnt;
          left_cnt -= a_for_iteration[j];
          min_res = min(min_res, left_sum + right_sum);

          right_cnt += a_for_iteration[j];
          right_sum += right_cnt;
        }
        cur_ans += min_res;
        l = r;
      }
    }
    ans = min(ans, cur_ans);
  };

  for (long long i = 2; i * i <= sum; ++i) {
    if (!(sum % i)) {
      while (!(sum % i)) {
        sum /= i;
      }
      for (int j = 0; j < n; ++j) {
        a_for_iteration[j] = a[j] % i;
      }
      try_for_divisor(i);
    }
  }

  if (sum > 1) {
    for (int j = 0; j < n; ++j) {
      a_for_iteration[j] = a[j] % sum;
    }
    try_for_divisor(sum);
  }
  cout << ans << "\n";

  return 0;
}
