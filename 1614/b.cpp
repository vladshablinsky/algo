#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i].first);
    v[i].second = i;
  }
  sort(v.begin(), v.end(), std::greater<pair<int, int>>());

  long long result = 0;
  vector<int> ans(n);
  for (int i = 0; i < n; ++i) {
    ans[v[i].second] = (1 + (i / 2)) * (-1 + 2 * (i % 2));
    result += mabs(ans[v[i].second]) * 2ll * v[i].first;
  }

  printf("%lld\n0 ", result);
  for (auto el: ans) {
    printf("%d ", el);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
