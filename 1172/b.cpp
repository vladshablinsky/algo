#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MOD = 998244353;

int factorials[MAXN];
int degrees[MAXN];

void init_factorials() {
  factorials[0] = 1;
  factorials[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    factorials[i] = (factorials[i - 1] * 1ll * i) % MOD;
  }
}

int main() {
  init_factorials();

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    cin >> from >> to;
    degrees[from - 1]++;
    degrees[to - 1]++;
  }

  int ans = n;
  for (int i = 0; i < n; ++i) {
    ans = (ans * 1ll * factorials[degrees[i]]) % MOD;
  }
  cout << ans << "\n";
  return 0;
}
