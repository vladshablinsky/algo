#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

int a[105][105];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == 'C') {
        a[i][j] = 1;
      }
    }
  }

  int ans = 0;

  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if (a[i][j] == 1) {
        ++cnt;
      }
    }
    ans += cnt * (cnt - 1) / 2;
  }

  for (int i = 0; i < n; ++i) {
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      if (a[j][i] == 1) {
        ++cnt;
      }
    }
    ans += cnt * (cnt - 1) / 2;
  }
  cout << ans << "\n";
  return 0;
}
