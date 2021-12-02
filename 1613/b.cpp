#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int mn = *std::min_element(a, a + n);

  for (int i = 0, j = 0; i < n && j < n / 2 ; ++i) {
    if (a[i] == mn) {
      continue;
    }
    printf("%d %d\n", a[i], mn);
    ++j;
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
