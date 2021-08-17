#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MOD = 1000000000 + 7;

int fact[MAXN];
int a[MAXN];

void init_fact() {
  fact[0] = 1;
  fact[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fact[i] = (fact[i - 1] * 1ll * i) % MOD;
  }
}

int binpow(int x, int p) {
  if (p == 0) {
    return 1;
  } else {
    if (p % 2) {
      return (x * 1ll * binpow(x, p - 1)) % MOD;
    } else {
      long long res = binpow(x, p / 2);
      return (res * res) % MOD;
    }
  }
}

int modinv(int x) {
  return binpow(x, MOD - 2);
}

int modmul(int x, int y) {
  return (x * 1ll * y) % MOD;
}

int solve() {
  int n;
  cin >> n;

  int target;
  cin >> a[0];
  target = a[0];

  for (int i = 1; i < n; ++i) {
    cin >> a[i];
    target &= a[i];
  }

  int cnt_target = 0;
  for (int i = 0; i < n; ++i) {
    cnt_target += (a[i] == target);
  }

  if (cnt_target < 2) {
    return 0;
  } else {
    int fact_part = fact[n - 2];
    int bin_coeff_part = modinv(modmul(fact[cnt_target - 2], fact[2]));
    bin_coeff_part = modmul(2, modmul(bin_coeff_part, fact[cnt_target]));
    return modmul(fact_part, bin_coeff_part);
  }
}

int main() {
  init_fact();

  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
