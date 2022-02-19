#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  int target = 1;
  int idx = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    if (i + 1 == target && v[i] == target) {
      ++target;
    } else if (v[i] == target) {
      idx = i;
    }
  }
  reverse(v.begin() + target - 1, v.begin() + idx + 1);
  for (auto el: v) {
    printf("%d ", el);
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
