#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1005;
const int MOD = 1000000007;
int c[MAXN][MAXN];

void calc_c() {
  for (int i = 0; i < MAXN; ++i) {
    c[i][i] = 1;
    c[i][0] = 1;
  }
  for (int i = 1; i < MAXN; ++i) {
    for (int j = 1; j < i; ++j) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  sort(v.begin(), v.end(), std::greater<int>());
  int from = k - 1;
  int to = k - 1;
  while (from > 0 && v[from - 1] == v[k - 1]) {
    --from;
  }
  while (to < n - 1 && v[to + 1] == v[k - 1]) {
    ++to;
  }
  cout << c[to - from + 1][k - from] << "\n";
}

int main() {
  calc_c();
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
