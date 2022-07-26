#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool try_with(const vector<int>& v, int n, int m) {
  int res;
  bool wide_encountered = false;
  int gained_m = 0;
  for (auto el: v) {
    int width = el / n;
    if (width < 2) {
      continue;
    }
    if (gained_m < m) {
      gained_m += width;
    }

    if (width > 2) {
      wide_encountered = true;
    }
  }

  if (gained_m < m || ((m & 1) && !wide_encountered)) {
    return false;
  }
  return true;
}

void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  vector<int> a(k);
  for (auto& el: a) {
    scanf("%d", &el);
  }

  if (try_with(a, n, m) || try_with(a, m, n)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
