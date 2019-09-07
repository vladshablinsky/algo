#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  sort(a, a + n);
  int ans = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] >= ans) {
      ++ans;
    }
  }
  cout << ans - 1 << "\n";
  return 0;
}
