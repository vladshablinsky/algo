#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
  int n, x, y;
  string s;
  cin >> n >> x >> y;
  cin >> s;

  int ans = 0;
  for (int i = 1; i <= y; ++i) {
    ans += (s[s.length()  - i] != '0');
  }

  ans += (s[s.length() - y - 1] != '1');

  for (int i = y + 2; i <= x; ++i) {
    ans += (s[s.length() - i] != '0');
  }

  cout << ans << "\n";
  return 0;
}
