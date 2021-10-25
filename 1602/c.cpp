#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXP = 30;

void solve() {
  vector<int> cnt_bits(MAXP + 1, 0);

  int n;
  scanf("%d", &n);
  int el;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &el);
    for (int j = 0; j <= MAXP; ++j) {
      if (el & (1 << j)) {
        ++cnt_bits[j];
      }
    }
  }

  for (int k = 1; k <= n; ++k) {
    bool all_div = true;
    for (int j = 0; j <= MAXP; ++j) {
      if (cnt_bits[j] % k != 0) {
        all_div = false;
        break;
      }
    }
    if (all_div) {
      printf("%d ", k);
    }
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
