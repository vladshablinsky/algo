#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const long long MAX_R = 1000000000ll * 1000000000ll;
const long long MOD = 1000000000 + 7;

long long cur_cnt_numbers_odd = 1;
long long cur_cnt_numbers_even;
long long sum_cnt_numbers_to_phase[70];
long long sum_cnt_even_to_phase[70];

void init() {
  int phase = 1;
  do {
    sum_cnt_numbers_to_phase[phase] = sum_cnt_numbers_to_phase[phase - 1];
    sum_cnt_even_to_phase[phase] = sum_cnt_even_to_phase[phase - 1];
    if (phase & 1) { // odd phase, add odd, double even
      sum_cnt_numbers_to_phase[phase] += cur_cnt_numbers_odd;
      cur_cnt_numbers_even = cur_cnt_numbers_odd * 2ll;
    } else {  // even phase, add even, double odd
      sum_cnt_numbers_to_phase[phase] += cur_cnt_numbers_even;
      sum_cnt_even_to_phase[phase] += cur_cnt_numbers_even;
      cur_cnt_numbers_odd = cur_cnt_numbers_even * 2ll;
    }
    ++phase;
  } while (sum_cnt_numbers_to_phase[phase - 1] < MAX_R);
}

long long sum_r(long long r) {
  int phase = 0;
  while (sum_cnt_numbers_to_phase[phase] < r) {
    ++phase;
  }

  long long cnt_numbers_to_skip = sum_cnt_numbers_to_phase[phase] - r;
  long long odd_cnt = sum_cnt_numbers_to_phase[phase] - sum_cnt_even_to_phase[phase];
  long long even_cnt = sum_cnt_even_to_phase[phase];

  if (phase & 1) {  // odd phase, some odd numbers are skipped.
    odd_cnt -= cnt_numbers_to_skip;
  } else {
    even_cnt -= cnt_numbers_to_skip;
  }

  odd_cnt %= MOD;
  even_cnt %= MOD;

  return ((odd_cnt * odd_cnt) % MOD + (even_cnt * (even_cnt + 1)) % MOD) % MOD;
}

int main() {
  init();
  long long l, r;
  cin >> l >> r;
  cout << (sum_r(r) - sum_r(l - 1) + MOD) % MOD << "\n";
  return 0;
}
