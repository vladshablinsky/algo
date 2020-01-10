//#pragma comment(linker, "/STACK:36777216")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXQ = 200005;
const int MAXN = 400002;
const int MAXPOW = 100000;
const int MAXP = 302;
const int MOD = 1e9 + 7;

vector<int> fact[MAXP];
vector<int> pows[MAXP];  // only prime pows here exist

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
  for (int i = 2; i <= MAXP; ++i) {
    int cur_n = i;
    for (int j = 2; j * j <= cur_n; ++j) {
      while (cur_n % j == 0) {
        fact[i].push_back(j);
        cur_n /= j;
      }
    }
    if (cur_n != 1) {
      fact[i].push_back(cur_n);
    }

    // prime, let's factorize. (There will be 60 of them)
    //if (cur_n == i) {
    //  pows[cur_n].resize(MAXN);
    //  pows[cur_n][0] = 1;
    //  for (int pw = 1; pw < MAXN; ++pw) {
    //    pows[cur_n][pw] = (pows[cur_n][pw - 1] * 1ll * cur_n) % MOD;
    //  }
    //}
  }
}

int a[MAXN];

struct node {
  unordered_map<int, long long> mp;
  unordered_map<int, long long> multiplier;
  int length;
  node(): length(1) {}
} t[4 * MAXN];


void add_factors_to_mp(const vector<int> &factors, unordered_map<int, long long> &mp) {
  for (auto cur_f: factors) {
    mp[cur_f]++;
  }
}

void merge_to_target(
    const unordered_map<int, long long> &x,
    unordered_map<int, long long> &target
    ) {
  for (auto &el: x) {
    target[el.first] += el.second;
  }
}

void build(int v, int tl, int tr) {
  if (tl == tr) {
    add_factors_to_mp(fact[a[tl]], t[v].mp);
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    merge_to_target(t[v * 2].mp, t[v].mp);
    merge_to_target(t[v * 2 + 1].mp, t[v].mp);
    t[v].length = (tr - tl + 1);
  }
}

void push(int v) {
  if (!t[v].multiplier.empty()) {
    for (auto &el: t[v].multiplier) {
      t[v].mp[el.first] += t[v].length * el.second;
      if (t[v].length != 1) {
        t[v * 2].multiplier[el.first] += el.second;
        t[v * 2 + 1].multiplier[el.first] += el.second;
      }
    }

    t[v].multiplier.clear();
  }
}

void multiply(int v, int tl, int tr, int l, int r, int multiplier) {
  if (l > r) {
    return;
  }

  push(v);

  if (tl == l && tr == r) {
    for (auto el: fact[multiplier]) {
      t[v].multiplier[el]++;
    }
  } else {
    int tm = (tl + tr) / 2;
    multiply(v * 2, tl, tm, l, min(tm, r), multiplier);
    multiply(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, multiplier);
    for (auto el: fact[multiplier]) {
      t[v].mp[el] += (r - l + 1);
    }
  }
}

void get_product(int v, int tl, int tr, int l, int r, unordered_map<int, long long> &ans) {
  if (l > r) {
    return;
  }

  push(v);
  if (tl == l && tr == r) {
    merge_to_target(t[v].mp, ans);
  } else {
    int tm = (tl + tr) / 2;
    get_product(v * 2, tl, tm, l, min(tm, r), ans);
    get_product(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, ans);
  }
}

int get_phi(const unordered_map<int, long long> &prime_factors) {
  long long ans = 1;
  for (auto &el: prime_factors) {
    int factor = el.first;
    long long power = el.second;
    if (factor != 1) {
      ans = (ans * binpow(factor, power - 1)) % MOD;
      ans = (ans * (factor - 1)) % MOD;
    }
  }
  return ans;
}

int main() {
  init_aux();
  int n, q;
  scanf("%d%d", &n, &q);
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
      unordered_map<int, long long> ans;
      get_product(1, 0, n - 1, l - 1, r - 1, ans);
      printf("%d\n", get_phi(ans));
    }
  }
  return 0;
}
