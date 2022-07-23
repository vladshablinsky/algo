#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

bool solve() {
  int k;
  scanf("%d", &k);

  int a[3];
  for (int i = 0; i < 3; ++i) {
    scanf("%d", &a[i]);
  }

  return !(a[k - 1] == 0 || a[a[k - 1] - 1] == 0);
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
