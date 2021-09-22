#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  long long diff_x = x[n / 2] - x[(n - 1) / 2] + 1;
  long long diff_y = y[n / 2] - y[(n - 1) / 2] + 1;
  printf("%lld\n", diff_x * diff_y);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
