#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long transitions[4][3] = {{0, 0, 0}, {1, 2, 3}, {2, 3, 1}, {3, 1, 2}};

long long gen_for_block(long long block_id, int inblock_id) {
  long long ans = 0;

  int shift = 0;
  while (block_id) {
    long long cur_two_bit_mask = block_id & 3;
    ans |= ((transitions[cur_two_bit_mask][inblock_id]) << shift);
    shift += 2;
    block_id /= 4;
  }
  return ans;
}

void solve(long long n) {
  int k = 0;
  long long pow = 1;
  long long sum = 3;
  long long remain = n;
  while (sum < n) {
    remain = n - sum; // remain is never zero!
    pow *= 4;
    k += 2;
    sum += pow * 3;
  }

  long long block_id = (remain - 1) / 3; // 0-indexed
  int inblock_id = (remain - block_id * 3) - 1; // 0-indexed

  long long ans = ((inblock_id + 1ll) << k) | gen_for_block(block_id, inblock_id);
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    long long n;
    cin >> n;
    solve(n);
  }
  return 0;
}
