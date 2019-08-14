#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 300005;

int main() {
  int n;
  long long ans = 0;
  string s;
  cin >> s;

  n = s.length();
  int r = n - 1;
  for (int l = n - 3; l >= 0; --l) {
    int k = 1;
    while (l + 2 * k <= r) {
      if (s[l] == s[l + k] && s[l] == s[l + 2 * k]) {
        r = l + 2 * k - 1;
        break;
      }
      ++k;
    }

    ans += (n - 1 - r);
  }
  cout << ans << "\n";

  return 0;
}
