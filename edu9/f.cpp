#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2505;
int a[MAXN][MAXN];
int min_in_line[MAXN];

int n;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[i][j]);
    }
  }

  for (int i = 0; i < n; ++i) {
    min_in_line[i] = 1000000000;
    for (int j = 0; j < n; ++j) {
      min_in_line[i] = min(min_in_line[i], a[i][j]);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j && a[i][j] != 0) {
        printf("NOT MAGIC\n");
        return 0;
      }
      if (a[i][j] != a[j][i]) {
        printf("NOT MAGIC\n");
        return 0;
      }
      if (a[i][j] > max(min_in_line[i], min_in_line[j])) {
        cout << "MIN IN LINE " << i << min_in_line[i] << endl;
        cout << "MIN IN LINE " << j << min_in_line[j] << endl;
        printf("NOT MAGIC\n");
        return 0;
      }
    }
  }
  printf("MAGIC\n");
  return 0;
}
