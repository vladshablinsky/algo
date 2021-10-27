#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  int same_as_first_i = 1;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);

    if (i && mabs(a[i]) == mabs(a[0])) {
      same_as_first_i = i;
    }
  }

  swap(a[1], a[same_as_first_i]);
  vector<int> b(n);
  int i = 0;
  while (i < n) {
    if (i + 3 == n) {
      int shift = 0;
      do {
        int i1 = i + shift;
        int i2 = i + (1 + shift) % 3;
        int i3 = i + (2 + shift) % 3;
        b[i1] = -(a[i2] + a[i3]);
        b[i2] = a[i1];
        b[i3] = a[i1];
      } while (b[i + shift++] == 0);
      i += 3;
    } else {
      if (mabs(a[i]) == mabs(a[i + 1])) {
        b[i] = 1;
        b[i + 1] = a[i] * a[i + 1] < 0 ? 1: -1;
      } else {
        b[i] = -a[i + 1];
        b[i + 1] = a[i];
      }
      i += 2;
    }
  }
  swap(b[1], b[same_as_first_i]);

  for (auto e: b) {
    printf("%d ", e);
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
