#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }
  int max_min = 0;
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    max_min = max(min(a[i], b[i]), max_min);
    mx = max(mx, max(a[i], b[i]));
  }
  printf("%d\n", mx * max_min);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}

