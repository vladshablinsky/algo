#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int& modadd(int& target, int val) {
  target = (target + val) % MOD;
  return target;
}

int modmul(int a, int b) {
  return (a * 1ll * b) % MOD;
}

int solve() {
  int planes, decay;
  cin >> planes >> decay;

  if (decay == 1) {
    return 1;
  }

  if (planes == 1) {
    return 2;
  }

  vector<int> lr(planes - 1, 0); // left to right lr[0] -- left bord.
  vector<int> rl(planes - 1, 0); // right to left rl[0] -- right bord.
  rl.back() = 1; // simulate one particle reflected from leftmost plane

  auto& prev = rl;
  auto& cur = lr;

  int ans = 2;
  for (int i = decay; i - 1 >= 1; --i) {
    int acc = 0;
    for (int j = 0; j < planes - 1; ++j) {
      modadd(acc, *(prev.rbegin() + j));
      cur[j] = acc;
      modadd(ans, cur[j]);
    }
    swap(cur, prev);
  }
  return ans;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
