#include <iostream>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    printf("%d ", (i + 1) % n + 1);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    solve();
  }
}
