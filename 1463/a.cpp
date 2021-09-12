#include <iostream>
#include <cstdio>

using namespace std;

bool solve() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  if ((a + b + c) % 9) {
    return false;
  }
  int k = (a + b + c) / 9;
  return min(a, min(b, c)) >= k;
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
