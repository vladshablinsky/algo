#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAX_POWER = 60;
int fact[MAX_POWER];

vector<long long> get_divisors(long long d) {
  vector<long long> ans;
  for (long long i = 2; i * i <= d; ++i) {
    if (d % i == 0) {
      ans.push_back(i);
      while (d % i == 0) {
        d /= i;
      }
    }
  }
  if (d != 1) {
    ans.push_back(d);
  }
  return ans;
}

long long gcd(long long a, long long b) {
  if (!b) {
    return a;
  }
  return gcd(b, a % b);
}

int binpow(int a, int pow) {
  if (pow == 0) {
    return 1;
  } else {
    if (pow % 2) {
      return (a * 1ll * binpow(a, pow - 1)) % MOD;
    } else {
      int res = binpow(a, pow / 2);
      return (res * 1ll * res) % MOD;
    }
  }
}

void init_fact() {
  fact[0] = fact[1] = 1;
  for (int i = 2; i < MAX_POWER; ++i) {
    fact[i] = (fact[i - 1] * 1ll * i) % MOD;
  }
}

int cnt_pathes(long long a, long long b, const vector<long long> &divs) {
  if (a == b) {
    return 1;
  }
  int sum_powers = 0;
  int product_fact_powers = 1;
  for (auto divisor: divs) {
    int res = 0;
    while (a % divisor == 0) {
      res++;
      a /= divisor;
    }
    while (b % divisor == 0) {
      res--;
      b /= divisor;
    }
    if (res < 0) {
      res = -res;
    }
    sum_powers += res;
    product_fact_powers = (product_fact_powers * 1ll * fact[res]) % MOD;
  }
  return (fact[sum_powers] * 1ll * binpow(product_fact_powers, MOD - 2)) % MOD;
}

int solve(long long a, long long b, const vector<long long> &divs) {
  long long gcd_ab = gcd(a, b);
  return (cnt_pathes(a, gcd_ab, divs) * 1ll * cnt_pathes(b, gcd_ab, divs)) % MOD;
}

int main() {
  long long d;
  int q;
  scanf("%lld%d", &d, &q);

  init_fact();
  auto divs = get_divisors(d);
  for (int i = 0; i < q; ++i) {
    long long from, to;
    scanf("%lld%lld", &from, &to);
    printf("%d\n", solve(from, to, divs));
  }
  return 0;
}
