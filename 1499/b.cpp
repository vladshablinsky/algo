#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 105;
// f[i][flag] -- we're on i'th symbol,
// f[i][flag] -- is there exist such a removal so that flag --
// is whether we remove all consequent zeros or not
int f[MAXN][2];

bool solve() {
  int n;
  string s;
  cin >> s;
  n = s.length();

  f[0][0] = true;
  f[1][0] = true;
  f[1][1] = true;

  for (int i = 2; i <= n; ++i) {
    auto cur_c = s[i - 1];
    auto prev_c = s[i - 2];
    if (cur_c == '0') {
      f[i][0] = f[i - 1][0];
      // must delete current
      f[i][1] = (f[i - 1][0] && prev_c == '0') || (f[i - 1][1] && prev_c == '1');
    } else {
      f[i][1] = f[i - 1][1];
      // must delete current
      f[i][0] = (f[i - 1][0] && prev_c == '0');
    }
  }

  return f[n][1] || f[n][0];
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
