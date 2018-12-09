#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 256;
int a[MAX_N][MAX_N];
int row_xor[MAX_N];
int col_xor[MAX_N];

int main() {
  int n, m;
  int xor_rows = 0;
  int xor_cols = 0;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> row_xor[i];
    xor_rows ^= row_xor[i];
  }
  for (int j = 0; j < m; ++j) {
    cin >> col_xor[j];
    xor_cols ^= col_xor[j];
  }

  if (xor_rows != xor_cols) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    a[0][0] = xor_cols  ^ col_xor[0] ^ row_xor[0];
    for (int j = 1; j < m; ++j) {
      a[0][j] = col_xor[j];
    }
    for (int i = 1; i < n; ++i) {
      a[i][0] = row_xor[i];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cout << a[i][j] << " ";
      }
      cout << "\n";
    }
  }
  return 0;
}
