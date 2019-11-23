#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

const int MAXN = 105;
const int MOD = 1e9 + 7;
int v[MAXN];

struct Matrix {
  int a[MAXN][MAXN];

  Matrix() {
    for (int i = 0; i < MAXN; ++i) {
      for (int j = 0; j < MAXN; ++j) {
        a[i][j] = 0;
      }
    }
  }

  static Matrix make_e() {
    Matrix result;
    for (int i = 0; i < MAXN; ++i) {
      result.a[i][i] = 1;
    }
    return result;
  }

  Matrix operator*(const Matrix& other) {
    Matrix result;
    for (int k = 0; k < MAXN; ++k) {
      for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
          result.a[i][j] = (result.a[i][j] + (a[i][k] * 1ll * other.a[k][j]) % MOD) % MOD;
        }
      }
    }

    return result;
  }
};

void print_mx(Matrix mx, int k) {
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      cout << mx.a[i][j] << " ";
    }
    cout << endl;
  }
}

int binpow(int el, int pow) {
  if (pow == 0) {
    return 1;
  }

  if (pow & 1) {
    return (el * 1ll * binpow(el, pow - 1)) % MOD;
  } else {
    int res = binpow(el, pow / 2);
    return (res * 1ll * res) % MOD;
  }
}

Matrix binpow(Matrix mx, int pow) {
  Matrix res = Matrix::make_e();
  while (pow) {
    if (pow & 1) {
      res = res * mx;
    }

    mx = mx * mx;
    pow /= 2;
  }
  return res;
}

int main() {
  int n, k;
  int a = 0;
  int b = 0;

  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    a += (v[i] == 0);
    b += (v[i] == 1);
  }

  int l = 0;
  for (int i = 0; i < a; ++i) {
    l += (v[i] == 1);
  }

  // initialization;
  int mx = min(a, b);
  if (mx == 0) {
    cout << "1\n";
    return 0;
  }

  Matrix res;
  for (int j = 0; j <= mx; ++j) {
    // swap within left + swap within right + swap zero vs zero + swap one vs one
    res.a[j][j] = (a * (a - 1) / 2 + b * (b - 1) / 2 + (a - j) * j + (b - j) * j);
    // swap zero from left with one from right to get j ones on the left.
    if (j) {
      res.a[j - 1][j] = (a - (j - 1)) * (b - (j - 1));
    }
    // swap one from left with zero from right.
    if (j < mx) {
      res.a[j + 1][j] = (j + 1) * (j + 1);
    }
  }

  res = binpow(res, k);
  int p = res.a[l][0];
  int q = p;
  for (int j = 1; j <= mx; ++j) {
    q = (q + res.a[l][j]) % MOD;
  }
  int ans = (p * 1ll * binpow(q, MOD - 2)) % MOD;
  cout << ans << "\n";
  return 0;
}
