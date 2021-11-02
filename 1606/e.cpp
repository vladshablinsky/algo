#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 505;
const int MOD = 998244353;

int f[MAXN][MAXN];
int c[MAXN][MAXN];
int pows[MAXN][MAXN];

int modadd(int& a, int b) {
  a += b;
  a %= MOD;
  return a;
}

int modmul(int a, int b) {
  return (a * 1ll * b) % MOD;
}

void init_c() {
  for (int i = 0; i < MAXN; ++i) {
    c[i][0] = 1;
    c[i][i] = 1;
  }
  for (int i = 1; i < MAXN; ++i) {
    for (int j = 1; j < i; ++j) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
  }
}

void init_pows() {
  for (int i = 0; i < MAXN; ++i) {
    pows[i][0] = 1;
    for (int j = 1; j < MAXN; ++j) {
      pows[i][j] = modmul(pows[i][j - 1], i);
    }
  }
}

int main() {
  init_c();
  init_pows();

  int n, x;
  scanf("%d%d", &n, &x);

  f[n][0] = 1;
  for (int i = n; i >= 2; --i) {
    for (int j = 0; j <= x; ++j) {
      if (f[i][j]) {
        for (int k = i; k >= 0; --k) {
          int hp = min(i + j - 1, x);

          modadd(f[k][hp], modmul(f[i][j], modmul(c[i][i - k], pows[hp - j][i - k])));
          // printf("(%d, %d) -> (%d, %d) : += %d * %d * %d\n", i, j, k, hp, f[i][j], c[i][i - k], pows[hp - j][i - k]);
        }
      }
    }
  }

  int ans = 0;
  for (int j = 0; j <= x; ++j) {
    modadd(ans, f[0][j]);
  }
  cout << ans << "\n";
}
