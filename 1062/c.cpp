#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 10;

int pref[MAXN];
int ans_ones[MAXN];
int zeros[MAXN];
int a[MAXN];

void init_ans_ones() {
  int zero = 0;
  int one = 1;
  int result = 0;
  for (int i = 1; i < MAXN; ++i) {
    result = (result + one) % MOD;
    ans_ones[i] = result;
    zero = (zero + one) % MOD;
    zeros[i] = zero;
    one = (one + one) % MOD;
  }
}

int main() {
  init_ans_ones();
  int n, q;
  scanf("%d%d", &n, &q);
  string s;
  cin >> s;
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + (s[i - 1] == '1');
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    int cnt_ones = pref[r] - pref[l - 1];
    int cnt_zeros = r - l + 1 - cnt_ones;
    cout << (ans_ones[cnt_ones] + zeros[cnt_ones] * 1ll * ans_ones[cnt_zeros]) % MOD << "\n";
  }

  return 0;
}
