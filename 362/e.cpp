#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 1e5 + 5;
const long long MOD = 1e9 + 7;
long long a[MAX_N];
bool is_even = false;

long long p = 1;
long long q = 2;

long long binpow(long long x, int long long pow) {
  if (pow == 0) {
    return 1;
  } else if (pow % 2 == 0) {
    long long t = binpow(x, pow / 2);
    return (t * 1ll * t) % MOD;
  } else {
    return (x * 1ll * binpow(x, pow - 1)) % MOD;
  }
}

long long divide(long long x, long long y) {
  return ((x % MOD) * 1ll * binpow(y, MOD - 2)) % MOD;
}

int main() {
  int k;
  cin >> k;

  for (int i = 0; i < k; ++i) {
    cin >> a[i];
    is_even |= (a[i] % 2 == 0);
  }

  for (int i = 0; i < k; ++i) {
    q = binpow(q, a[i]);
  }

  q = divide(q, 2);

  if (is_even) {
    p = (q + 1) % MOD;
  } else {
    p = (q - 1 + MOD) % MOD;
  }
  p = divide(p, 3);

  cout << p << "/" << q << "\n";
  return 0;
}
