#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

const int INF = 1e9;

bool check(long long x, const unordered_set<long long> &divisors) {
  int cnt_divisors = 0;
  for (long long i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      ++cnt_divisors;
      if (!divisors.count(i)) {
        return false;
      }
      if (!divisors.count(x / i)) {
        return false;
      }

      if (x / i != i) {
        ++cnt_divisors;
      }
    }
  }
  return divisors.size() == cnt_divisors;
}

void solve() {
  int n;
  scanf("%d", &n);
  unordered_set<long long> st;
  int mn = INF;
  int mx = -INF;
  for (int i = 0; i < n; ++i) {
    int d;
    scanf("%d", &d);
    st.insert(d);
    mn = min(mn, d);
    mx = max(mx, d);
  }

  if (check(mn * 1ll * mx, st)) {
    cout << mn * 1ll * mx << "\n";
  } else {
    cout << "-1\n";
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
