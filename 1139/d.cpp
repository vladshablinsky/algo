#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 5;

int f[MAXN];
int phi[MAXN];
vector<int> divisors[MAXN];

void init(int n) {
  phi[0] = phi[1] = 0;
  for (int i = 1; i <= n; ++i) {
    if (i > 1) {
      phi[i] += (i - 1);
    }
    for (int j = i + i; j <= n; j += i) {
      divisors[j].push_back(i);
      phi[j] -= phi[i];
    }
  }
}

int binpow(int x, int pow) {
  if (pow == 0) {
    return 1;
  }

  if (pow & 1) {
    return (x * 1ll * binpow(x, pow - 1)) % MOD;
  } else {
    int res = binpow(x, pow / 2);
    return (res * 1ll * res) % MOD;
  }
}

int div_mod(int a, int b) {
  return (a * 1ll * binpow(b, MOD - 2)) % MOD;
}

int mul_mod(int a, int b) {
  return (a * 1ll * b) % MOD;
}

int add_mod(int a, int b) {
  return (a + b) % MOD;
}

int cnt_ortagonal(int x, int m) {
  if (x == 1) {
    return m;
  }

  // cout << "cnt_ort " << x << " " << m << endl;
  int ans = m;
  vector<int> prime_factors;
  while (x != 1) {
    prime_factors.push_back(divisors[x].size() == 1 ? x : divisors[x][1]);
    while (!(x % prime_factors.back())) {
      x /= prime_factors.back();
    }
  }

  for (int i = 1; i < (1 << prime_factors.size()); ++i) {
    int cur_div = 1;
    int parity = 0;
    for (int j = 0; j < prime_factors.size(); ++j) {
      if (i & (1 << j)) {
        parity ^= 1;
        cur_div *= prime_factors[j];
      }
    }

    if (parity) {
      //cout << "- " << m / cur_div << endl;
      ans -= m / cur_div;
    } else {
      //cout << "+ " << m / cur_div << endl;
      ans += m / cur_div;
    }
  }
  // cout << "result: " << ans << endl;
  return ans;
}

int main() {
  int m;
  scanf("%d", &m);

  init(m);

  f[1] = 0;
  int invm = div_mod(1, m);
  for (int i = 2; i <= m; ++i) {
    //cout << "i = " << i << endl;
    int rhs = 0;

    for (auto &gcd: divisors[i]) {
      //cout << "gcd: " << gcd << ", cnt: " << cnt_ortagonal(i / gcd, m / gcd) << endl;
      rhs = add_mod(rhs, mul_mod(f[gcd], cnt_ortagonal(i / gcd, m / gcd)));
    }
    rhs = add_mod(1, mul_mod(rhs, invm));
    f[i] = mul_mod(rhs, div_mod(1, MOD + 1 - mul_mod(m / i, invm)));
    //cout << "f(" << i <<  ") = " << f[i] << endl;
  }

  int ans = 1;
  for (int i = 1; i <= m; ++i) {
    ans = add_mod(ans, mul_mod(f[i], invm));
  }

  cout << ans << "\n";
  return 0;
}
