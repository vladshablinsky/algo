#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

void solve() {
  string s;
  cin >> s;
  vector<int> last(3, 0);
  int ans = INF;
  for (int i = 0; i < s.length(); ++i) {
    last[s[i] - '1'] = i + 1;
    if (last[0] && last[1] && last[2]) {
      ans = min(ans, *max_element(last.begin(), last.end()) - *min_element(last.begin(), last.end()) + 1);
    }
  }

  if (ans == INF) {
    cout << "0\n";
  } else {
    cout << ans << "\n";
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }

  return 0;
}
