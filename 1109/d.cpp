#include <iostream>
#include <cstdio>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1000005;
int fact[MAXN];

int binpow(int a, int b) {
  if (b == 0) {
    return 1;
  }
  if (b % 2) {
    return (a * 1ll * binpow(a, b - 1)) % MOD;
  } else {
    int res = binpow(a, b / 2);
    return (res * 1ll * res) % MOD;
  }
}

void init_fact() {
  fact[0] = 1;
  fact[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fact[i] = (fact[i - 1] * 1ll * i) % MOD;
  }
}

int mod_div(int a, int b) {
  return (a * 1ll * binpow(b, MOD - 2)) % MOD;
}

int A(int n, int k) {
  if (n == 0 || k == 0) {
    return 1;
  }
  return mod_div(fact[n], fact[n - k]);
}

int C(int n, int k) {
  if (k > n) {
    return 0;
  }
  if (n == 0 || k == 0) {
    return 1;
  }
  return mod_div(fact[n], (fact[k] * 1ll * fact[n - k]) % MOD);
}

int mod_mul(int a, int b) {
  return (a * 1ll * b) % MOD;
}

int cayley(int x, int y) {
  if (x == y) {
    return 1;
  }
  return mod_mul(y, binpow(x, x - y - 1));
}

int main() {
  init_fact();
  int n, m, a, b;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  int ans = 0;

  // cnt of vertices between a and b
  for (int i = 0; i <= n - 2; ++i) {
    int cur_ans = mod_mul(mod_mul(C(m - 1, i), binpow(m, n - i - 2)), mod_mul(A(n - 2, i), cayley(n, i + 2)));
    ans = (ans + cur_ans) % MOD;
  }

  printf("%d\n", ans);
  return 0;
}


