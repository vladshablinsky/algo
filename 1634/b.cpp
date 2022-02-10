#include <iostream>

using namespace std;

void solve() {
  int n, x;
  long long y;
  scanf("%d%d%lld", &n, &x, &y);

  int parity_income = 0;
  for (int i = 0, el = 0; i < n; ++i) {
    scanf("%d", &el);
    parity_income += el;
    parity_income %= 2;
  }
  if (((x + parity_income) & 1) == (y & 1)) {
    printf("Alice\n");
  } else {
    printf("Bob\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
