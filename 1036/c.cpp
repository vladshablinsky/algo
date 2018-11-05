#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long> nums;

void generate_nums(long long cur, int cnt_non_zeros) {
  //cout << "gen " << cur << " " << length << endl;
  if (cur) {
    nums.push_back(cur);
  }
  if (cur < (1ll << 62) / 10) {
    if (cur) {
      generate_nums(cur * 10, cnt_non_zeros);
    }
    if (cnt_non_zeros < 3) {
      for (int i = 1; i <= 9; ++i) {
        generate_nums(cur * 10 + i, cnt_non_zeros + 1);
      }
    }
  }
}

int cnt_numbers_less_eq(long long x) {
  int l = 0;
  int r = nums.size() - 1;
  int idx = -1;
  while (l <= r) {
    int m = (l + r) / 2;
    if (nums[m] <= x) {
      idx = max(m, idx);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return idx + 1;
}

int main() {
  nums.push_back(0);
  generate_nums(0ll, 0);
  sort(nums.begin(), nums.end());
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    long long l, r;
    cin >> l >> r;
    cout << cnt_numbers_less_eq(r) - cnt_numbers_less_eq(l - 1) << "\n";
  }
  return 0;
}
