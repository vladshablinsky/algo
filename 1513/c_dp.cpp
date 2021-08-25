#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXM = 200015;
const int MOD = 1000000007;
int f[MAXM];

void calc_f() {
  for (int i = 0; i < 10; ++i) {
    f[i] = 1;
  }
  for (int i = 10; i < MAXM; ++i) {
    f[i] = (f[i - 9] + f[i - 10]) % MOD;
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  int ans = 0;
  do {
    ans = (ans + f[n % 10 + m]) % MOD;
    n /= 10;
  } while (n);
  printf("%d\n", ans);
}

int main() {
  calc_f();
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
