#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<char> vs(m, 'B');

  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    int p1 = el - 1;
    int p2 = m - el;
    if (vs[min(p1, p2)] == 'A') {
      vs[max(p1, p2)] = 'A';
    } else {
      vs[min(p1, p2)] = 'A';
    }
  }
  for (auto el: vs) {
    printf("%c", el);
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
