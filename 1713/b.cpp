#include <iostream>
#include <cstdio>

using namespace std;

bool solve() {
  int n;
  bool sane = true;
  bool goes_down = false;
  int prev = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int cur;
    scanf("%d", &cur);

    if (cur < prev) {
      goes_down = true;
    }

    if (cur > prev && goes_down) {
      sane = false;
    }

    prev = cur;
  }
  return sane;
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
