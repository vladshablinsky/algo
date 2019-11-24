#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

const int INF = 1e9;

void solve() {
  int n;
  scanf("%d", &n);
  int min_end = INF;
  int max_start = 0;
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    min_end = min(min_end, r);
    max_start = max(max_start, l);
  }
  printf("%d\n", max(0, max_start - min_end));
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
