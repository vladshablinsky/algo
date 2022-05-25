#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int MAXN = 200005;

bool solve() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  vector<int> b(n);
  vector<int> shifts(n + 1, 0);

  for (auto &el: a) {
    scanf("%d", &el);
  }
  for (auto &el: b) {
    scanf("%d", &el);
  }

  int b_idx = 0;
  for (int i = 0; i < n; ++i) {
    if (a[i] == b[b_idx]) {
      ++b_idx;
      while (b_idx < n && a[i] == b[b_idx] && shifts[a[i]]) {
        ++b_idx;
        --shifts[a[i]];
      }
    } else {
      shifts[a[i]]++;
    }
  }

  return b_idx == n;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
