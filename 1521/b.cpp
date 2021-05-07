#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

const int PRIME = 1e9 + 7;
const int MAXN = 200005;
const int INF = 1e9;
int a[MAXN];
tuple<int, int, int, int> ans[MAXN];


void solve() {
  int n;
  scanf("%d", &n);
  set<pair<int, int>> st;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }


  int start_idx = n % 2;
  int cnt_ops = 0;
  for (int i = start_idx; i < n; i += 2) {

    // if there element less than current to the right
    if (a[i + 1] <= a[i]) {
      a[i] = PRIME;
      ans[cnt_ops++] = {i, i + 1, PRIME, a[i + 1]};
    } else {
      ans[cnt_ops++] = {i, i + 1, a[i + 1], a[i]};
      ans[cnt_ops++] = {i, i + 1, PRIME, a[i]};

      a[i] = PRIME;
      a[i + 1] = a[i];
    }
  }

  printf("%d\n", cnt_ops);
  for (int idx = 0; idx < cnt_ops; ++idx) {
    auto [i, j, x, y] = ans[idx];
    printf("%d %d %d %d\n", i + 1, j + 1, x, y);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }

  return 0;
}
