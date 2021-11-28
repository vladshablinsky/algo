#include <iostream>
#include <cstdio>

using namespace std;

int solve() {
  int a, b;
  scanf("%d%d", &a, &b);
  if (a > b) {
    swap(a, b);
  }

  if (a <= (a + b) / 4) {
    return a;
  } else {
    return (a + b) / 4;
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
