#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int a[105];

void wrap_swap(int i, int j) {
  printf("%d %d\n", i + 1, j + 1);
  swap(a[i], a[j]);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 0; i < n - 1; ++i) {
      if (a[i] > a[i + 1]) {
        flag = true;
        wrap_swap(i, i + 1);
      }
    }
  }
  return 0;
}
