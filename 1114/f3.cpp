//#pragma comment(linker, "/STACK:36777216")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int MAXQ = 200005;
const int MAXN = 400002;
const int MAXPOW = 100000;
const int MAXP = 302;
const int MOD = 1e9 + 7;

long long masks[MAXP];

int primes_idx[MAXP];
vector<int> primes;
vector<int> divided_primes;

int a[MAXN];
int n;

struct node {
  int val;
  int multiplier;
  int length;
  long long mask;
  long long mask_to_push;
  node(): val(1), multiplier(1), mask(1) {}
} t[4 * MAXN];

int binpow(int a, long long b) {
  if (b == 0) {
    return 1;
  } else {
    if (b & 1) {
      return (a * 1ll * binpow(a, b - 1)) % MOD;
    } else {
      long long res = binpow(a, b / 2);
      return (res * res) % MOD;
    }
  }
}

void init_aux() {
  // factorize them all
  for (int i = 2; i < MAXP; ++i) {
    int cur_n = i;
    for (int j = 2; j * j <= cur_n; ++j) {
      while (cur_n % j == 0) {
        cur_n /= j;
        masks[i] |= (1ll << primes_idx[j]);
      }
    }

    // i is prime
    if (cur_n == i) {
      primes.push_back(i);
      divided_primes.push_back(((i - 1) * 1ll * binpow(i, MOD - 2)) % MOD);
      primes_idx[i] = primes.size();
    }

    if (cur_n != 1) {
      masks[i] |= (1ll << primes_idx[cur_n]);
    }
  }
}

void build(int v, int tl, int tr) {
  if (tl == tr) {
    t[v].val = a[tl];
    t[v].mask = masks[a[tl]];
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    t[v].val = (t[v * 2].val * 1ll * t[v * 2 + 1].val) % MOD;
    t[v].mask = t[v * 2].mask | t[v * 2 + 1].mask;
    t[v].length = (tr - tl + 1);
  }
}

void push(int v) {
  if (t[v].mask_to_push) {
    t[v].mask |= t[v].mask_to_push;
    t[v].val = (t[v].val * 1ll * binpow(t[v].multiplier, t[v].length)) % MOD;
    if (t[v].length != 1) {
      t[v * 2].multiplier = (t[v * 2].multiplier * 1ll * t[v].multiplier) % MOD;
      t[v * 2].mask_to_push |= t[v].mask_to_push;

      t[v * 2 + 1].multiplier = (t[v * 2 + 1].multiplier * 1ll * t[v].multiplier) % MOD;
      t[v * 2 + 1].mask_to_push |= t[v].mask_to_push;
    }
    t[v].multiplier = 1;
    t[v].mask_to_push = 0;
  }
}

void multiply(int v, int tl, int tr, int l, int r, int multiplier) {
  if (l > r) {
    return;
  }

  //printf("multiply %d (%d,%d), (%d,%d), * %d\n", v, tl, tr, l, r, multiplier);

  if (tl == l && tr == r) {
    t[v].multiplier = (t[v].multiplier * 1ll * multiplier) % MOD;
    t[v].mask_to_push |= masks[multiplier];
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    multiply(v * 2, tl, tm, l, min(tm, r), multiplier);
    multiply(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, multiplier);

    t[v].val = (t[v].val * 1ll * binpow(multiplier, r - l + 1)) % MOD;
    t[v].mask |= masks[multiplier];
  }
}

pair<int, long long> get_product(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return {1, 0};
  }

  push(v);
  if (tl == l && tr == r) {
    return {t[v].val, t[v].mask};
  } else {
    int tm = (tl + tr) / 2;
    auto l_prod = get_product(v * 2, tl, tm, l, min(tm, r));
    auto r_prod = get_product(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
    return {
      (l_prod.first * 1ll * r_prod.first) % MOD,
      l_prod.second | r_prod.second
    };
  }
}

int main() {
  int q;
  scanf("%d%d", &n, &q);
  init_aux();
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  build(1, 0, n - 1);

  for (int i = 0; i < q; ++i) {
    int l, r;
    string s;
    cin >> s;
    if (s == "MULTIPLY") {
      int x;
      scanf("%d%d%d", &l, &r, &x);
      multiply(1, 0, n - 1, l - 1, r - 1, x);
    } else {
      scanf("%d%d", &l, &r);
      auto product = get_product(1, 0, n - 1, l - 1, r - 1);
      for (int j = 1; j < 63; ++j) {
        if (product.second & (1ll << j)) {
          product.first = (product.first * 1ll * divided_primes[j - 1]) % MOD;
        }
      }
      printf("%d\n", product.first);
    }
  }
  return 0;
}
