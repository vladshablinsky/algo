#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int MAXN = 505;

int a[MAXN][MAXN];
int b[MAXN][MAXN];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 0 ; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      scanf("%d", &b[i][j]);
    }
  }

  // go diagonals;
  unordered_map<int, int> mp;
  for (int k = 0; k < n + m - 1; ++k) {
    mp.clear();
    int i = min(k, n - 1);
    int j = max(0, k - (n - 1));

    while (i >= 0 && j < m) {
      mp[a[i][j]]++;
      mp[b[i][j]]--;
      --i;
      ++j;
    }

    for (auto &el: mp) {
      if (el.second != 0) {
        cout << "NO\n";
        return 0;
      }
    }
  }
  cout << "YES\n";
  return 0;
}
