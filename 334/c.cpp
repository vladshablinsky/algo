#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;

// f(i, j, k)
// standing on element i, what is the greatest length of the
// string 101010101 that ends with j and has k pairs of same consecutive
// elements
int f[MAX_N][2][3];
string s;
int n;

int main() {
  cin >> n;
  string s = ".";
  string t;
  cin >> t;
  s += t;

  for (int i = 1; i <= n; ++i) {
    if (s[i] == '0') {
      f[i][0][0] = max(f[i - 1][0][0], f[i - 1][1][0] + 1);
      f[i][0][1] = max(f[i - 1][0][1], max(f[i - 1][0][0] + 1, f[i - 1][1][1] + 1));
      f[i][0][2] = max(f[i - 1][0][2], max(f[i - 1][0][1] + 1, f[i - 1][1][2] + 1));
      f[i][1][0] = f[i - 1][1][0];
      f[i][1][1] = f[i - 1][1][1];
      f[i][1][2] = f[i - 1][1][2];
    } else {
      f[i][1][0] = max(f[i - 1][1][0], f[i - 1][0][0] + 1);
      f[i][1][1] = max(f[i - 1][1][1], max(f[i - 1][1][0] + 1, f[i - 1][0][1] + 1));
      f[i][1][2] = max(f[i - 1][1][2], max(f[i - 1][1][1] + 1, f[i - 1][0][2] + 1));
      f[i][0][0] = f[i - 1][0][0];
      f[i][0][1] = f[i - 1][0][1];
      f[i][0][2] = f[i - 1][0][2];
    }
  }

  int ans = 0;
  for (int last = 0; last <= 1; ++last) {
    for (int k = 0; k <= 2; ++k) {
      ans = max(ans, f[n][last][k]);
    }
  }

  cout << ans << "\n";

  return 0;
}
