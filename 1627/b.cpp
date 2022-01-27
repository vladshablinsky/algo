#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int dist(int n, int m, int i, int j) {
  return max(
    max(i + j, n - 1 - i + m - 1 -j),
    max(i + m - 1 - j, n - 1 - i + j)
  );
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);

  // for all cells except first calc
  // the farest Tina can sit. Then sort all these
  // and on the Tina's side remove them from Rahuls pool

  vector<int> v;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int optimal_dist = dist(n, m, i, j);
      v.push_back(optimal_dist);
    }
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n * m; ++i) {
    printf("%d ", v[i]);
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
