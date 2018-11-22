#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <set>

using namespace std;

const int MAX_N = 1e5 + 5;
const int MOD = 1e9 + 7;

int a[MAX_N];
unordered_map<int, int> f_prev;
unordered_map<int, int> f;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  f_prev[0] = 1;
  for (int i = 0; i < n; ++i) {
    vector<int> divisors;
    for (int j = 1; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        divisors.push_back(j);
        divisors.push_back(a[i] / j);
      }
    }
    for (auto x: divisors) {
      int take_x = 0;
      int no_take_x = 0;
      bool possible_get_x = false;
      if (f_prev.find(x - 1) != f_prev.end()) {
        possible_get_x = true;
        take_x = f_prev[x - 1];
      }
      if (f_prev.find(x) != f_prev.end()) {
        possible_get_x = true;
        no_take_x = f_prev[x];
      }

      if (possible_get_x) {
        f[x] = (take_x + no_take_x) % MOD;
      }
    }

    for (auto el: f) {
      f_prev[el.first] = el.second;
    }
    f.clear();
  }
  int ans = 0;
  for (auto el: f_prev) {
    if (el.first) {
      ans = (ans + el.second) % MOD;
    }
  }
  cout << ans << "\n";
  return 0;
}
