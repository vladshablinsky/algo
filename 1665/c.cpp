#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> cnts(n, 0);

  for (int i = 1; i < n; ++i) {
    int from;
    scanf("%d", &from);
    cnts[from - 1]++;
  }

  for (int i = 0, l = cnts.size(); i < l; ++i) {
    while (!cnts[i] && i < l) {
      swap(cnts.back(), cnts[i]);
      cnts.pop_back();
      --l;
    }
  }

  // We initialize the layers with most cnts to least so
  // that the ones with most cnt have more time to spread
  int required_time = cnts.size() + 1;

  sort(cnts.begin(), cnts.end());

  // last infected is the root, therefore all the others
  // will always wait one tick when initializing the root
  // so 1 is always subtracted
  for (int i = 0; i < cnts.size(); ++i) {
    cnts[i] = max(0, cnts[i] - 2 - i);
  }

  // Ok, now all layers are infected and we need to wait some more time.
  // binsearch that time
  int l = 0; int r = MAXN;
  int ans = MAXN;
  while (l <= r) {
    int m = (l + r) / 2;

    // check code here
    int to_infect = 0;
    for (auto cnt: cnts) {
      to_infect += max(0, cnt - m);
    }

    if (to_infect <= m) {
      ans = min(ans, m);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  printf("%d\n", required_time + ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
