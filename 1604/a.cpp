#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 105;

void solve() {
  int n;
  scanf("%d", &n);
  int el;
  int cnt_inserted = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &el);
    cnt_inserted += max(0, el - (i + cnt_inserted));
  }

  printf("%d\n", cnt_inserted);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
