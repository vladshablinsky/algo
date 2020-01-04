#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;

long long n;
int m;

vector<vector<int>> mul(const vector<vector<int>> &a, const vector<vector<int>> &b) {
  vector<vector<int>> c(m);
  for (auto &row: c) {
    row = vector<int>(m, 0);
  }

  for (int k = 0; k < m; ++k) {
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < m; ++j) {
        c[i][j] = (c[i][j] + (a[i][k] * 1ll * b[k][j]) % MOD) % MOD;
      }
    }
  }
  return c;
}

vector<vector<int>> binpow(vector<vector<int>> &v, long long p) {
  if (p == 0) {
    vector<vector<int>> res(v.size());
    for (int i = 0; i < res.size(); ++i) {
      res[i] = vector<int>(v.size());
      res[i][i] = 1;
    }
    return res;
  }

  if (p % 2) {
    return mul(binpow(v, p - 1), v);
  } else {
    auto res = binpow(v, p / 2);
    return mul(res, res);
  }
}

int main() {
  cin >> n >> m;
  if (m > n) {
    cout << 1 << "\n";
    return 0;
  }
  if (m == n) {
    cout << 2 << "\n";
    return 0;
  }

  // m < n

  vector<vector<int>> v(m);
  for (int i = 0; i < m; ++i) {
    v[i] = vector<int>(m, 0);
    if (i == 0) {
      v[0][m - 1] += 1;
    } else if (i == m - 1) {
      v[m - 1][m - 1] += 1;
    }

    if (i) {
      v[i][i - 1] += 1;
    }
  }

  v = binpow(v, n - m);

  int ans = 0;
  for (int i = 0; i < m - 1; ++i) {
    ans = (ans + v[i][m - 1]) % MOD;
  }
  ans = (ans * 1ll + v[m - 1][m - 1] * 2) % MOD;
  cout << ans << "\n";
  return 0;
}
