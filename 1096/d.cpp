#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const string NEEDLE = "hard";
const int MAXN = 1e5 + 5;
const long long INF = 1000000000 * 1ll * 1000000000;

int a[MAXN];

int main() {
  int n;
  string s;
  scanf("%d", &n);
  cin >> s;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  long long ans = INF;
  vector<long long> prev_f(n + 1, 0);
  vector<long long> cur_f(n + 1);

  auto smart_upd = [](long long &target, long long val) {
    if (target == -1) {
      target = val;
    } else {
      target = min(target, val);
    }
  };

  for (int i = 1; i <= n; ++i) {
    prev_f[i] = prev_f[i - 1] + a[i - 1] * (s[i - 1] == NEEDLE[0]);
  }
  ans = prev_f[n];

  for (int k = 0; k + 1 < NEEDLE.length(); ++k) {
    fill(cur_f.begin(), cur_f.end(), -1);
    for (int i = 1; i <= n; ++i) {
      if (s[i - 1] == NEEDLE[k] && prev_f[i - 1] != -1) {
        smart_upd(cur_f[i], prev_f[i - 1]);
      }
      if (cur_f[i - 1] != -1) {
        smart_upd(cur_f[i], cur_f[i - 1] + a[i - 1] * (s[i - 1] == NEEDLE[k + 1]));
      }
    }

    if (cur_f[n] == -1) {
      cout << "0\n";
      return 0;
    } else {
      ans = min(ans, cur_f[n]);
    }
    swap(cur_f, prev_f);
  }
  cout << ans << "\n";
  return 0;
}
