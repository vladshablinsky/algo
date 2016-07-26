#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX_N = 2e5 + 5;

int cnt_p[MAX_N];

int binpow(int x, int pow) {
  if (pow == 0) {
    return 1;
  } else {
    if (pow % 2 == 0) {
      int ans = binpow(x, pow / 2);
      return (ans * 1ll * ans) % MOD;
    } else {
      return (x * 1ll * binpow(x, pow - 1)) % MOD;
    }
  }
}

int main() {
  int n;
  cin >> n;
  bool has_odd = false;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    cnt_p[t]++;
  }

  for (int i = 0; i < MAX_N; ++i) {
    if (cnt_p[i] && (cnt_p[i] % 2)) {
      has_odd = true;
      break;
    }
  }

  int k = 1;

  for (int i = 1; i < MAX_N; ++i) {
    if (cnt_p[i]) {
      if (has_odd) {
        k = (k * 1ll * binpow(i, cnt_p[i])) % MOD;
      } else {
        k = (k * 1ll * binpow(i, cnt_p[i] / 2)) % MOD;
      }
    }
  }

  bool already_rooted = false;
  for (int i = 1; i < MAX_N; ++i) {
    if (cnt_p[i]) {
      if (has_odd && !already_rooted && (cnt_p[i] % 2 == 1)) {
        k = binpow(k, (cnt_p[i] + 1) / 2);
        already_rooted = true;
      } else {
        k = binpow(k, cnt_p[i] + 1);
      }
    }
  }
  cout << k << "\n";
  return 0;
}
