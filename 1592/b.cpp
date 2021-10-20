#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;

int a[MAXN];
int b[MAXN];

bool solve() {
  int n;
  int x;
  scanf("%d%d", &n, &x);

  bool sorted = true;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];
    if (i && a[i - 1] > a[i]) {
      sorted = false;
    }
  }

  sort(b, b + n);

  if (sorted) {
    return true;
  }

  if (x == n) {
    return sorted;
  }

  bool not_swappable_sorted = true;
  for (int i = n - x; i < x; ++i) {
    not_swappable_sorted &= (a[i] == b[i]);
  }

  return not_swappable_sorted;
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
