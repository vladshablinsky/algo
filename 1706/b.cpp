#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> color_idxs(n);
  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    color_idxs[el - 1].push_back(i);
  }

  // dp for each
  for (auto idxs: color_idxs) {
    int max_f_even_idx = 0;
    int max_f_odd_idx = 0;
    for (int idx: idxs) {

      // odd idx
      if (idx & 1) {
        max_f_odd_idx = max(1, max_f_even_idx + 1);
      } else { // even idx
        max_f_even_idx = max(1, max_f_odd_idx + 1);
      }
    }
    printf("%d ", max(max_f_even_idx, max_f_odd_idx));
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
