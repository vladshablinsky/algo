#include <iostream>
#include <cstdio>

using namespace std;

const int INF = 1000000000;

void solve() {
  int n;
  string s;
  cin >> n;
  cin >> s;

  int ans = INF;
  for (char c = 'a'; c <= 'z'; ++c) {
    int l = 0;
    int r = s.length() - 1;
    int curans = 0;
    while (l < r) {
      if (s[l] == s[r]) {
        ++l;
        --r;
      } else if (s[l] == c) {
        ++l;
        ++curans;
      } else if (s[r] == c) {
        --r;
        ++curans;
      } else {
        curans = INF;
        break;
      }
    }

    ans = min(ans, curans);
  }
  if (ans == INF) {
    ans = -1;
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
