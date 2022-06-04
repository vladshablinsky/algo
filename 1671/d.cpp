#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

constexpr int kInf = 1000000000;

void solve() {
  int n, x;
  scanf("%d%d", &n, &x);
  long long diff = 0;
  int prev, cur;
  scanf("%d", &prev);

  int mn = prev;
  int mx = prev;

  int min_adj_diff1 = prev - 1;
  int min_adj_diff2 = abs(prev - x);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &cur);
    diff += abs(cur - prev);
    mn = min(mn, cur);
    mx = max(mx, cur);

    min_adj_diff1 = min(min_adj_diff1, cur + prev - 2 - abs(cur - prev));
    min_adj_diff2 = min(min_adj_diff2, abs(cur - x) + abs(prev - x) - abs(cur - prev));

    prev = cur;
  }

  min_adj_diff1= min(min_adj_diff1, prev - 1);
  min_adj_diff2 = min(min_adj_diff2, abs(prev - x));

  if (mn == mx) {
    diff += min_adj_diff1;
    if (x > mn) {
      diff += min_adj_diff2;
    }
  } else {
    if (x > mn) { // meaning there's (mn, mn + 1) somwhere
      min_adj_diff1 = min(min_adj_diff1, mn - 1 + mn - 1);
    }

    if (x >= mx - 1) { // meaning there's (mx - 1, mx) somewhere
      min_adj_diff2 = min(min_adj_diff2, abs(x - mx) + abs(mx - 1 - x) - 1);
    }

    diff += min_adj_diff1;
    if (x > mx) {
      diff += min_adj_diff2;
    }
  }

  // cout << "diff1: " << min_adj_diff1 << endl;
  // cout << "diff2: " << min_adj_diff2<< endl;

  cout << diff << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
