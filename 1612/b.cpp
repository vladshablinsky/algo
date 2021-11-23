#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

void solve() {
  int n;
  int a, b;
  scanf("%d%d%d", &n, &a, &b);

  set<int> l, r;
  // left half min is a
  // right half max is b
  for (int i = 1; i < a; ++i) {
    r.insert(i);
  }
  r.insert(b);
  for (int i = b + 1; i <= n; ++i) {
    l.insert(i);
  }
  l.insert(a);

  int j = a;
  for (j = a + 1; j < b && l.size() < n / 2; ++j) {
    l.insert(j);
  }
  while (j < b) {
    r.insert(j++);
  }


  if (l.size() == n / 2 && r.size() == n / 2) {
    for (auto el: l) {
      printf("%d ", el);
    }
    for (auto el: r) {
      printf("%d ", el);
    }
  } else {
    printf("-1");
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
