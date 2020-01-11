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
const int MAXT = 1048577;
const int MAXPOW = 100000;
const int MAXP = 302;
const int MOD = 1e9 + 7;

vector<pair<int, int>> fact[MAXP];
vector<int> primes;
int a[MAXN];
int n;

struct node {
  int val;
  int multiplier;
  node(): val(0), multiplier(1) {}
};

vector<node> t[MAXP];
int t_lengths[MAXT];

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
      int x = 1;
      while (cur_n % j == 0) {
        x = (x * 1ll * j) % MOD;
        cur_n /= j;
      }
      if (x != 1) {
        fact[i].push_back({j, x});
      }
    }
    if (cur_n != 1) {
      fact[i].push_back({cur_n, cur_n});
    }

    // i is prime
    if (fact[i].size() == 1 && fact[i].back().second == fact[i].back().first) {
      primes.push_back(i);
      t[i].resize(min(4 * n, MAXT);
    }
  }
}

void build(int factor, int v, int tl, int tr) {
  if (tl == tr) {
    for (auto &el: fact[a[tl]]) {
      if (el.first == factor) {
        t[factor][v].val = el.second;
        break;
      }
    }
    t_lengths[v] = 1;
  } else {
    int tm = (tl + tr) / 2;
    build(factor, v * 2, tl, tm);
    build(factor, v * 2 + 1, tm + 1, tr);
    if (t[factor][v * 2].val || t[factor][v * 2 + 1].val) {
      t[factor][v].val = (max(1, t[factor][v * 2].val) * 1ll * max(1, t[factor][v * 2 + 1].val)) % MOD;
    }
    t_lengths[v] = (tr - tl + 1);
  }
}

void push(int factor, int v) {
  if (t[factor][v].multiplier != 1) {
    t[factor][v].val = (max(1, t[factor][v].val) * 1ll * binpow(t[factor][v].multiplier, t_lengths[v])) % MOD;

    if (t_lengths[v] != 1) {
      t[factor][v * 2].multiplier = (t[factor][v * 2].multiplier * 1ll * t[factor][v].multiplier) % MOD;
      t[factor][v * 2 + 1].multiplier = (t[factor][v * 2 + 1].multiplier * 1ll * t[factor][v].multiplier) % MOD;
    }

    t[factor][v].multiplier = 1;
  }
}

void multiply(int factor, int v, int tl, int tr, int l, int r, int multiplier) {
  if (l > r) {
    return;
  }

  push(factor, v);

  if (tl == l && tr == r) {
    t[factor][v].multiplier = (t[factor][v].multiplier * 1ll * multiplier) % MOD;
  } else {
    int tm = (tl + tr) / 2;
    multiply(factor, v * 2, tl, tm, l, min(tm, r), multiplier);
    multiply(factor, v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, multiplier);

    t[factor][v].val = (max(t[factor][v].val, 1) * 1ll * binpow(multiplier, r - l + 1)) % MOD;
  }
}

int get_product(int factor, int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return 0;
  }

  push(factor, v);
  if (tl == l && tr == r) {
    return t[factor][v].val;
  } else {
    int tm = (tl + tr) / 2;
    int l_prod = get_product(factor, v * 2, tl, tm, l, min(tm, r));
    int r_prod = get_product(factor, v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
    if (l_prod || r_prod) {
      return (max(1, l_prod) * 1ll * max(1, r_prod)) % MOD;
    } else {
      return 0;
    }
  }
}

int main() {
  int q;
  scanf("%d%d", &n, &q);
  init_aux();
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (auto prime: primes) {
    build(prime, 1, 0, n - 1);
  }

  //cout << "built!\n";

  for (int i = 0; i < q; ++i) {
    int l, r;
    string s;
    cin >> s;
    if (s == "MULTIPLY") {
      int x;
      scanf("%d%d%d", &l, &r, &x);
      for (auto el: fact[x]) {
        multiply(el.first, 1, 0, n - 1, l - 1, r - 1, el.second);
      }
    } else {
      scanf("%d%d", &l, &r);
      int result = 1;
      for (auto prime: primes) {
        //cout << "product of " << prime << " is " << get_product(prime, 1, 0, n - 1, l - 1, r - 1) << endl;
        int product = get_product(prime, 1, 0, n - 1, l - 1, r - 1);
        if (product) {
          //cout << "product of " << prime << " is " << get_product(prime, 1, 0, n - 1, l - 1, r - 1) << endl;
          result = (result * 1ll * product) % MOD;
          result = (result * 1ll * binpow(prime, MOD - 2)) % MOD;
          result = (result * 1ll * (prime - 1)) % MOD;
        }
      }
      printf("%d\n", result);
    }
  }
  return 0;
}
