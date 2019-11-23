#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 5;
const long long INF = 1000000000ll * 1000000000ll;
int a[MAXN];

int main() {
  int n;
  int sum = 0;
  long long ans = INF;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    sum += a[i];
  }

  auto try_for_divisor = [&](int divisor) {
    long long cur_ans = 0;
    int l = 0;
    while (l < n) {
      if (a[l]) {
        long long min_cur_sum = INF;
        int cur_cnt = 0;
        int r = l;
        while (cur_cnt < divisor) {
          cur_cnt += a[r++];
        }
        --r;

        long long right_sum = 0;
        long long left_sum = 0;
        int right_cnt = 0;
        for (int j = r; j >= l;--j) {
          right_cnt += a[j];
          right_sum += right_cnt;
        }

        int left_cnt = 0;
        for (int j = l; j <= r; ++j) {
          right_sum -= right_cnt;
          right_cnt -= a[j];
          min_cur_sum = min(min_cur_sum, right_sum + left_sum);

          left_cnt += a[j];
          left_sum += left_cnt;
        }
        cur_ans += min_cur_sum;
        l = r + 1;
      } else {
        ++l;
      }
    }
    ans = min(ans, cur_ans);
  };

  bool has_good_divisors = false;
  for (int i = 2; i <= sum; ++i) {
    if (!(sum % i)) {
      has_good_divisors = true;
      try_for_divisor(i);
    }
  }

  if (!has_good_divisors) {
    cout << "-1\n";
  } else {
    cout << ans << "\n";
  }

  return 0;
}
