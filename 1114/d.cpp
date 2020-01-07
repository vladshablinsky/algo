#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 5005;

int c[MAXN];
int l[MAXN][MAXN];
int r[MAXN][MAXN];

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    if (i && c[i] == c[i - 1]) {
      --i;
      --n;
    }
    l[i][i] = 0;
    r[i][i] = 0;
  }

  // diagonal
  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < n - k; ++i) {
      int j = i + k;

      l[i][j] = min(
        l[i + 1][j] + (c[i + 1] != c[i]),
        r[i + 1][j] + (c[i] != c[j])
      );

      r[i][j] = min(
        r[i][j - 1] + (c[j - 1] != c[j]),
        l[i][j - 1] + (c[i] != c[j])
      );
    }
  }

  cout << min(l[0][n - 1], r[0][n - 1]) << "\n";
  return 0;
}
