#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 502;
const int MAXA = 1010;
const int INF = 1e9;

int a[MAXN];
int f[MAXN][MAXN];
int g[MAXN];

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    f[i][i] = a[i];
  }

  for (int len = 2; len <= n; ++len) {
    for (int start = 1; start + len - 1 <= n; ++start) {
      for (int mid = start; mid + 1 < start + len; ++mid) {
        if (f[start][mid] && f[start][mid] == f[mid + 1][start + len - 1]) {
          f[start][start + len - 1] = f[start][mid] + 1;
          break;
        }
      }
    }
  }

  for (int i = 1; i <= n; ++i) {
    g[i] = i;
    for (int j = 0; j < i; ++j) {
      if (f[j + 1][i]) {
        g[i] = min(g[i], g[j] + 1);
      }
    }
  }

  cout << g[n] << "\n";
  return 0;
}
