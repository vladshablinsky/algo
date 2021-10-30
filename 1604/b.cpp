#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 100005;
const int INF = 1e9;

bool solve() {
  int n;
  scanf("%d", &n);
  bool has_inc = false;
  int prev_el = 0;
  int el;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &el);
    if (prev_el >= el) {
      has_inc = true;
    }
    prev_el = el;
  }

  return (n % 2 == 0) || has_inc;
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
