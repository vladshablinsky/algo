#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  string s;
  cin >> s;

  bool is_pal = true;
  for (int i = 0; i < n / 2; ++i) {
    if (s[i] != s[n - 1 - i]) {
      is_pal = false;
      break;
    }
  }

  if (k == 0) {
    printf("1\n");
  } else {
    printf("%d\n", 1 + !is_pal);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
