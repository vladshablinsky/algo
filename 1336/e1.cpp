#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int MAXM = 36;
const int MOD = 998244353;

int n;
int m;
long long a[MAXN];

int binpow(int x, int p) {
  if (p == 0) {
    return 1;
  }
  if (p % 2) {
    return (x * 1ll * binpow(x, p - 1)) % MOD;
  } else {
    int res = binpow(x, p / 2);
    return (res * 1ll * res) % MOD;
  }
}

vector<pair<int, long long>> make_basis() {
  sort(a, a + n, std::greater<long long>());
  vector<pair<int, long long>> result;
  for (int i = 0; i < n; ++i) {
    long long cur_el = a[i];
    if (cur_el == 0) {
      continue;
    }

    for (auto el: result) {
      if ((1ll << el.first) & cur_el) {
        cur_el ^= el.second;
      }
    }

    if (cur_el) {
      int msb = 63 - __builtin_clzll(cur_el);
      result.push_back({msb, cur_el});
    }

    if (result.size() == m) { // basis is found.
      break;
    }
  }

  // elimination
  for (int i = 1; i < result.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      if (result[j].second & (1ll << result[i].first)) {
        result[j].second ^= result[i].second;
      }
    }
  }
  return result;
}

void solve_base_small(vector<pair<int, long long>> &basis) {
  int k = basis.size();
  // number of vectors in linear space that have i bits set.
  vector<int> cnt(m + 1, 0);
  for (int i = 0; i < (1 << k); ++i) {
    long long cur_linear_comb = 0;
    for (int j = 0; j < k; ++j) {
      if (i & (1 << j)) {
        cur_linear_comb ^= basis[j].second;
      }
    }

    cnt[__builtin_popcountll(cur_linear_comb)]++;
  }

  int cnt_non_basis_combinations = binpow(2, n - k);
  for (int i = 0; i <= m; ++i) {
    printf("%d ", int((cnt[i] * 1ll * cnt_non_basis_combinations) % MOD));
  }
  printf("\n");
}

void print_binary(int x) {
  for (int i = m; i >= 0; --i) {
    cout << (((1ll << i) & x) != 0);
  }
}

int prev_f[MAXM][(1 << (MAXM / 2))];
int cur_f[MAXM][(1 << (MAXM / 2))];
void solve_non_base_small(vector<pair<int, long long>> &basis) {
  int k = basis.size();

  vector<int> fixed_bits_ids;
  long long target_mask = 0;
  for (auto el: basis) {
    target_mask |= (1ll << el.first);
  }
  for (int i = 0; i <= m; ++i) {
    if (!(target_mask & (1ll << i))) {
      fixed_bits_ids.push_back(i);
    }
  }

  vector<int> floating_bits_basis;
  for (auto el: basis) {
    int floating_mask = 0;
    for (int i = 0; i < fixed_bits_ids.size(); ++i) {
      if (el.second & (1ll << fixed_bits_ids[i])) {
        floating_mask |= (1 << i);
      }
    }
    floating_bits_basis.push_back(floating_mask);
  }


  prev_f[0][0] = 1;
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j <= k; ++j) {
      for (int mask = 0; mask < (1 << (m - k)); ++mask) {
        cur_f[j][mask] = (prev_f[j][mask] +
            (j ? prev_f[j - 1][mask ^ floating_bits_basis[i]]: 0)) % MOD;
      }
    }
    swap(cur_f, prev_f);
  }

  vector<int> cnt(m + 1, 0);
  for (int j = 0; j <= k; ++j) {
    for (int mask = 0; mask < (1 << (m - k)); ++mask) {
      int cnt_set_bits = j + __builtin_popcountll(mask);
      cnt[cnt_set_bits] = (cnt[cnt_set_bits] + prev_f[j][mask]) % MOD;
    }
  }

  int cnt_non_basis_combinations = binpow(2, n - k);
  for (int i = 0; i <= m; ++i) {
    printf("%d ", int((cnt[i] * 1ll * cnt_non_basis_combinations) % MOD));
  }
  printf("\n");
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }

  vector<pair<int, long long>> basis = make_basis();
  if (basis.size() > m / 2) {
    solve_non_base_small(basis);
  } else {
    solve_base_small(basis);
  }
  return 0;
}
