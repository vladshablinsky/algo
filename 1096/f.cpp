#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

int a[MAXN];
int facts[MAXN];
bool known[MAXN];
int cnt_unknown_lesseq[MAXN];

int binpow(int a, int p) {
  if (p == 0) {
    return 1;
  } else {
    if (p % 2) {
      return (a * 1ll * binpow(a, p - 1)) % MOD;
    } else {
      int res = binpow(a, p / 2);
      return (res * 1ll * res) % MOD;
    }
  }
}

int modmul(int x, int y) {
  //return x * y;
  return (x * 1ll * y) % MOD;
}

int moddiv(int x, int y) {
  //return x / y;
  return (x * 1ll * binpow(y, MOD - 2)) % MOD;
}

int modadd(int x, int y) {
  //return x + y;
  return (x + y) % MOD;
}

void init_facts(int n) {
  facts[0] = 1;
  for (int i = 1; i <= n; ++i) {
    facts[i] = modmul(facts[i - 1], i);
  }
}

// pretty similar to merge sort
int cnt_inversions(int l, int r, vector<int> &v) {
  if (l >= r) {
    return 0;
  }
  int m = (l + r) / 2;
  int res = 0;
  res = modadd(res, cnt_inversions(l, m, v));
  res = modadd(res, cnt_inversions(m + 1, r, v));
  vector<int> lv(v.begin() + l, v.begin() + m + 1);
  vector<int> rv(v.begin() + m + 1, v.begin() + r + 1);
  int il = 0;
  int ir = 0;

  while (il < lv.size() && ir < rv.size()) {
    if (lv[il] > rv[ir]) {
      res = modadd(res, lv.size() - il);
      v[l + il + ir] = rv[ir];
      ++ir;
    } else {
      v[l + il + ir] = lv[il];
      ++il;
    }
  }

  while (il < lv.size()) {
    v[l + il + ir] = lv[il];
    ++il;
  }

  while (ir < rv.size()) {
    v[l + il + ir] = rv[ir];
    ++ir;
  }

  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  int cnt_unknown = 0;
  vector<int> knowns_v;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (a[i] == -1) {
      ++cnt_unknown;
    } else {
      known[a[i]] = true;
      knowns_v.push_back(a[i]);
    }
  }

  init_facts(n);
  for (int i = 1; i <= n; ++i) {
    cnt_unknown_lesseq[i] = cnt_unknown_lesseq[i - 1] + !known[i];
  }

  int cnt_unknown_left = 0;
  int total_inv_cnt = 0;
  if (cnt_unknown > 1) {
    int cnt_pairs;
    if (cnt_unknown & 1) {
      cnt_pairs = modmul((cnt_unknown - 1) / 2, cnt_unknown);
    } else {
      cnt_pairs = modmul(cnt_unknown - 1, cnt_unknown / 2);
    }
    total_inv_cnt = modmul(moddiv(facts[cnt_unknown], 2), cnt_pairs);
  }

  if (cnt_unknown) {
    for (int i = 0; i < n; ++i) {
      if (known[a[i]]) {
        int contribuition = modmul(cnt_unknown_lesseq[a[i]],
            modmul(cnt_unknown - cnt_unknown_left, facts[cnt_unknown - 1]));
        contribuition = modadd(contribuition, modmul(cnt_unknown - cnt_unknown_lesseq[a[i]],
              modmul(cnt_unknown_left, facts[cnt_unknown - 1])));
        total_inv_cnt = modadd(total_inv_cnt, contribuition);
      } else {
        ++cnt_unknown_left;
      }
    }
  }

  cout << modadd(moddiv(total_inv_cnt, facts[cnt_unknown]), cnt_inversions(0, knowns_v.size() - 1, knowns_v)) << "\n";
  return 0;
}
