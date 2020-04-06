#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

void solve(int n, long long k) {
  int x = n - 1;
  if (k == 1) {
    cout << "YES " << n - 1 << "\n";
    return;
  }
  long long cur_a = 0;
  long long cur_b = 0;
  long long cur_pow_four_for_a = 1;
  long long cur_pow_two_for_a = 2;
  while (x >= 0) {
    cur_a = max(1ll, -n + x - 2 + 2ll * cur_pow_two_for_a);
    //cout << "cur_a: " << cur_a << endl;
    if (cur_a > k) {
      break;
    }
    cur_b += cur_pow_four_for_a;

    //cout << x << ", A: " << cur_a << ", B: " << cur_b << endl;

    if (cur_a <= k && cur_b >= k) {
      cout << "YES " << x << "\n";
      return;
    }

    if (x == 0) {
      break;
    }

    long long turns_left = k - cur_b;
    long long debug_val = cur_b;
    if (turns_left / (cur_pow_two_for_a - 1) < cur_pow_two_for_a - 1) {
      //cout << turns_left << ", cur_pow_two_for_a - 1: " << cur_pow_two_for_a - 1 << endl;
      cout << "YES " << x << "\n";
      return;
    }

    // formula is (2^(n - x) - 1)^2 \times \sum_{i=0}^{x-1} 4^i
    long long multiplier = (cur_pow_two_for_a - 1) * (cur_pow_two_for_a - 1);
    turns_left -= multiplier;
    if (turns_left <= 0) {
      cout << "YES " << x << "\n";
      return;
    }

    debug_val += multiplier;
    long long cur_pow_four = 4;
    for (int i = 1; i <= x - 1; ++i) {
      if (turns_left / cur_pow_four < multiplier || turns_left / multiplier < cur_pow_four) {
        cout << "YES " << x << "\n";
        return;
      }
      turns_left -= multiplier * cur_pow_four;
      debug_val += multiplier * cur_pow_four;
      if (turns_left <= 0) {
        cout << "YES " << x << "\n";
        return;
      }
      cur_pow_four *= 4;
    }
    //cout << "debug_value: " << debug_val << endl;
    //cout << "turns_left:  " << turns_left << endl;
    cur_pow_four_for_a *= 4;
    cur_pow_two_for_a *= 2;
    --x;
  }
  cout << "NO\n";
}

int main() {
  int t;
  int x;
  long long k;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    cin >> x >> k;
    solve(x, k);
  }
  return 0;
}
