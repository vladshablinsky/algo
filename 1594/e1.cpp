#include <iostream>
#include <cstdio>

using namespace std;

const int MOD = 1000000007;

int binpow(int a, int p) {
  if (p == 0) {
    return 1;
  } else {
    if (p & 1) {
      return (a * 1ll * binpow(a, p - 1)) % MOD;
    } else {
      int res = binpow(a, p / 2);
      return (res * 1ll * res) % MOD;
    }
  }
}

int main() {
  int k;
  cin >> k;
  int four_squared_k = 4;
  for (int i = 0; i < k; ++i) {
    four_squared_k = (four_squared_k * 1ll * four_squared_k) % MOD;
  }
  int four_squared_inv = binpow(4 * 4, MOD - 2);
  cout << (6 * 1ll * four_squared_k * four_squared_inv) % MOD << "\n";
}
