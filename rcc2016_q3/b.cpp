#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

void solve() {
  int inversions = 0;
  int n;
  scanf("%d\n", &n);
  string a, b;
  cin >> a >> b;
  for (int i = 0; i < n - 1; ++i) {
    if (a[i] != b[i]) {
      ++inversions;
      a[i] = b[i];
      if (a[i + 1] == '0') {
        a[i + 1] = '1';
      } else {
        a[i + 1] = '0';
      }
    }
  }
  if (a[n - 1] != b[n - 1]) {
    printf("-1\n");
  } else {
    printf("%d\n", inversions);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
