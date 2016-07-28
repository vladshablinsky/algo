#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 505;

int a[MAX_N][MAX_N];

int main() {
  int n, k;
  cin >> n >> k;
  int cur_num = 1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < k - 1; ++j) {
      a[i][j] = cur_num++;
    }
  }

  int res = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = k - 1; j < n; ++j) {
      a[i][j] = cur_num++;
      if (j == k - 1) {
        res += a[i][j];
      }
    }
  }

  cout << res << "\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << a[i][j] << " ";
    }
    cout << "\n";
  }

  return 0;
}
