#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const long long MOD = 998244353;

struct dp {
  long long sum_all_digits;
  long long sum_less_digits;
  long long cnt_all_digits;
  long long sum_leading_zeros;
  long long cnt_leading_zeros;
  dp():
    sum_all_digits(0),
    sum_less_digits(0),
    cnt_all_digits(0),
    sum_leading_zeros(0),
    cnt_leading_zeros(0)
  {};
};

const int MAX_DIGITS = 20;
const int MAX_MASK = (1 << 11);

dp f[MAX_DIGITS][3][MAX_MASK];

void init_f() {
  for (int i = 0; i < MAX_DIGITS; ++i) {
    for (int j = 0; j < 3; ++j) {
      for (int k = 0; k < MAX_MASK; ++k) {
        f[i][j][k] = dp();
      }
    }
  }
}

long long res_for(long long x, int max_cnt, const vector<int> &available_digits) {
  init_f();
  long long pow_10 = 1;
  int i;
  f[0][0][0].cnt_all_digits = 1;

  for (i = 0; i < MAX_DIGITS && x; ++i) {
    int x_digit = x % 10;
    x /= 10;

    for (int mask = 0; mask < (1 << available_digits.size()); ++mask) {
      auto cur_equal = f[i][0];
      auto cur_less = f[i][1];
      auto cur_greater = f[i][2];
      auto next_equal = f[i + 1][0];
      auto next_less = f[i + 1][1];
      auto next_greater = f[i + 1][2];

      long long sum_all_and_less = (
        cur_less[mask].sum_all_digits +
        cur_less[mask].sum_less_digits +
        cur_equal[mask].sum_all_digits +
        cur_greater[mask].sum_all_digits +
        cur_greater[mask].sum_less_digits
      ) % MOD;

      // ignore current digit:
      // only less then possible
      next_less[mask].sum_less_digits += sum_all_and_less;
      next_less[mask].sum_less_digits %= MOD;

      // use current digit:
      long long digit_to_put;
      for (int k = 0, dig_mask = 1; k < available_digits.size(); ++k, dig_mask <<= 1) {
        digit_to_put = available_digits[k];
        if (digit_to_put > x_digit) {
          long long sum_cur_cnt_all_digits = cur_equal[mask].cnt_all_digits +
            cur_greater[mask].cnt_all_digits + cur_less[mask].cnt_all_digits +
            cur_less[mask].cnt_leading_zeros + cur_equal[mask].cnt_leading_zeros +
            cur_greater[mask].cnt_leading_zeros;

          next_greater[mask | dig_mask].cnt_all_digits += sum_cur_cnt_all_digits;
          next_greater[mask | dig_mask].sum_all_digits = (
            next_greater[mask | dig_mask].sum_all_digits +
            cur_equal[mask].sum_all_digits +
            cur_greater[mask].sum_all_digits +
            cur_less[mask].sum_all_digits +
            cur_less[mask].sum_leading_zeros +
            cur_equal[mask].sum_leading_zeros +
            cur_greater[mask].sum_leading_zeros +
            (((sum_cur_cnt_all_digits % MOD) * pow_10) % MOD) * digit_to_put
          ) % MOD;
        } else if (digit_to_put < x_digit) {
          long long sum_cur_cnt_all_digits = cur_equal[mask].cnt_all_digits +
            cur_greater[mask].cnt_all_digits + cur_less[mask].cnt_all_digits +
            cur_less[mask].cnt_leading_zeros + cur_equal[mask].cnt_leading_zeros +
            cur_greater[mask].cnt_leading_zeros;

          long long to_add = (
            cur_equal[mask].sum_all_digits +
            cur_greater[mask].sum_all_digits +
            cur_less[mask].sum_all_digits +
            cur_less[mask].sum_leading_zeros +
            cur_equal[mask].sum_leading_zeros +
            cur_greater[mask].sum_leading_zeros +
            (((sum_cur_cnt_all_digits % MOD) * pow_10) % MOD) * digit_to_put
          ) % MOD;

          if (digit_to_put == 0) {
            next_less[mask | dig_mask].cnt_leading_zeros += sum_cur_cnt_all_digits;
            next_less[mask | dig_mask].sum_leading_zeros += to_add;
          } else {
            next_less[mask | dig_mask].cnt_all_digits += sum_cur_cnt_all_digits;
            next_less[mask | dig_mask].sum_all_digits += to_add;
          }
          next_less[mask | dig_mask].sum_leading_zeros %= MOD;
          next_less[mask | dig_mask].sum_all_digits %= MOD;

        } else { // digit_to_put == x_digit
          if (cur_equal[mask].cnt_all_digits || cur_equal[mask].cnt_leading_zeros) {
            if (digit_to_put == 0) {
              next_equal[mask | dig_mask].cnt_leading_zeros = 1;
              next_equal[mask | dig_mask].sum_leading_zeros = (
                cur_equal[mask].sum_all_digits +
                cur_equal[mask].sum_leading_zeros
              ) % MOD;
            } else {
              next_equal[mask | dig_mask].cnt_all_digits = 1;
              next_equal[mask | dig_mask].sum_all_digits = (
                cur_equal[mask].sum_all_digits +
                cur_equal[mask].sum_leading_zeros +
                pow_10 * digit_to_put
              ) % MOD;
            }
          }

          if (digit_to_put == 0) {
            next_greater[mask | dig_mask].cnt_leading_zeros += (
              cur_greater[mask].cnt_all_digits +
              cur_greater[mask].cnt_leading_zeros
            );
            next_greater[mask | dig_mask].sum_leading_zeros = (
              next_greater[mask | dig_mask].sum_leading_zeros +
              cur_greater[mask].sum_all_digits +
              cur_greater[mask].sum_leading_zeros
            ) % MOD;

            next_less[mask | dig_mask].cnt_leading_zeros += (
              cur_less[mask].cnt_all_digits +
              cur_less[mask].cnt_leading_zeros
            );

            next_less[mask | dig_mask].sum_leading_zeros = (
              next_less[mask | dig_mask].sum_leading_zeros +
              cur_less[mask].sum_all_digits +
              cur_less[mask].sum_leading_zeros
            ) % MOD;
          } else {
            next_greater[mask | dig_mask].cnt_all_digits += (
              cur_greater[mask].cnt_all_digits +
              cur_greater[mask].cnt_leading_zeros
            );
            next_greater[mask | dig_mask].sum_all_digits = (
              next_greater[mask | dig_mask].sum_all_digits +
              cur_greater[mask].sum_all_digits +
              cur_greater[mask].sum_leading_zeros +
              ((((cur_greater[mask].cnt_all_digits +
                cur_greater[mask].cnt_leading_zeros) % MOD) * pow_10) % MOD) * digit_to_put
            ) % MOD;

            next_less[mask | dig_mask].cnt_all_digits += (
              cur_less[mask].cnt_all_digits +
              cur_less[mask].cnt_leading_zeros
            );
            next_less[mask | dig_mask].sum_all_digits = (
              next_less[mask | dig_mask].sum_all_digits +
              cur_less[mask].sum_all_digits +
              cur_less[mask].sum_leading_zeros +
              ((((cur_less[mask].cnt_all_digits +
                cur_less[mask].cnt_leading_zeros) % MOD) * pow_10) % MOD) * digit_to_put
            ) % MOD;
          }
        }
      }
    }

    pow_10 = (pow_10 * 10) % MOD;
  }

  int mask = (1 << available_digits.size()) - 1;
  long long res = 0;
  for (int mask = 0; mask < (1 << available_digits.size()); ++mask) {
    int cnt = 0;
    for (int j = 0; j < 10; ++j) {
      if ((mask & (1 << j)) != 0) {
        ++cnt;
      }
    }
    if (cnt >= 1 && cnt <= max_cnt) {
      long long cur_res = f[i][0][mask].sum_all_digits + f[i][1][mask].sum_all_digits +
        f[i][1][mask].sum_less_digits;
      res = (res + cur_res) % MOD;
    }
  }
  return res;
}

long long solve(long long l, long long r, int k) {
  long long ans = 0;
  vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  long long a = res_for(r, k, digits);
  long long b = res_for(l - 1, k, digits);
  ans = (ans + a) % MOD;
  ans = (ans - b + MOD) % MOD;
  return ans;
}

int main() {
  long long l, r;
  int k;
  cin >> l >> r >> k;
  cout << solve(l, r, k) << "\n";
  return 0;
}
