#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;

  if (c == 0) {
    if (a == b) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
    return 0;
  }
  if ((b - a) % c == 0 && (b - a) / c >= 0) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}
