#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

int main() {
  int q;
  scanf("%d", &q);

  for (int k = 0; k < q; ++k) {
    vector<string> mx;
    int n, m;
    scanf("%d%d\n", &n, &m);

    vector<int> cnt_row(n, 0);
    vector<int> cnt_col(m, 0);
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      mx.push_back(s);
      for (int j = 0; j < s.length(); ++j) {
        if (s[j] == '*') {
          cnt_row[i]++;
          cnt_col[j]++;
        }
      }
    }

    int ans = INF;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        ans = min(ans, (m - cnt_row[i]) + (n - cnt_col[j]) - (mx[i][j] == '.'));
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
