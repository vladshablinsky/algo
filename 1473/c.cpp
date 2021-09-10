#include <iostream>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 1; i <= 2 * k - n - 1; ++i) {
    printf("%d ", i);
  }
  for (int i = k; i > 2 * k - n - 1; --i) {
    printf("%d ", i);
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
