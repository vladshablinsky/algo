#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int read_best_prefix() {
  int n;
  scanf("%d", &n);
  int best_value = 0;
  int cur_val = 0;
  for (int i = 0; i < n; ++i) {
    int val;
    scanf("%d", &val);
    cur_val += val;
    best_value = max(best_value, cur_val);
  }
  return best_value;
}

void solve() {
  printf("%d\n", read_best_prefix() + read_best_prefix());
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
