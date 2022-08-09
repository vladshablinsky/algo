#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> v;
  for (int i = 1; i <= n; ++i) {
    v.push_back(i);
  }
  printf("%d\n", n);
  for (int i = 0; i < n; ++i) {
    for (auto el: v) {
      printf("%d ", el);
    }
    if (i + 1 < n) {
      swap(v[i], v[i + 1]);
    }
    printf("\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
