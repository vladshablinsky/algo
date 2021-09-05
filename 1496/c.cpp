#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
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
  vector<int> miners;
  vector<int> diamonds;
  for (int i = 0; i < 2 * n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x == 0) {
      miners.push_back(mabs(y));
    } else {
      diamonds.push_back(mabs(x));
    }
  }
  sort(miners.begin(), miners.end());
  sort(diamonds.begin(), diamonds.end());
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    auto aa = static_cast<double>(miners[i]);
    auto bb = static_cast<double>(diamonds[i]);
    ans += sqrt(aa * aa + bb * bb);
  }
  printf("%.9lf\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
