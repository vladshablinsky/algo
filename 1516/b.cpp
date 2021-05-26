#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 2005;
int a[MAXN];
int pref[MAXN];

bool solve() {
  int n;
  cin >> n;
  pref[0] = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    pref[i] = pref[i - 1] ^ a[i];
  }

  for (int i = 1; i < n; ++i) {
    int base_xor = pref[i];
    if (base_xor == (pref[n] ^ base_xor)) {
      return true;
    }
    for (int j = i + 1; j < n; ++j) {
      int middle = pref[j] ^ base_xor;
      int tail = pref[n] ^ pref[j];
      if (base_xor == middle && base_xor == tail) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
