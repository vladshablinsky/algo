#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

int pow_two[MAXN];

void init_pow_two() {
  pow_two[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    pow_two[i] = (pow_two[i - 1] * 2) % MOD;
  }
}

string a;
string b;

int main() {
  init_pow_two();
  int n, m;
  scanf("%d%d", &n, &m);
  cin >> a;
  cin >> b;

  int ans = 0;
  int cnt_ones_left = 0;

  int aligned_size = max(n, m);
  for (int i = 0; i < aligned_size; ++i) {
    if (i - (aligned_size - m) >= 0 && b[i - (aligned_size - m)] == '1') {
      ++cnt_ones_left;
    }

    if (i - (aligned_size - n) >= 0 && a[i - (aligned_size - n)] == '1') {
      ans = (pow_two[aligned_size - i - 1] * 1ll * cnt_ones_left + ans) % MOD;
    }
  }
  cout << ans << "\n";
  return 0;
}
