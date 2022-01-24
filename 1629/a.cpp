#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i].first);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i].second);
  }
  sort(v.begin(), v.end());

  for (int i = 0; i < n; ++i) {
    if (v[i].first <= k) {
      k += v[i].second;
    }
  }

  printf("%d\n", k);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
