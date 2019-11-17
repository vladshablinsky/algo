#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  int result_xor = 0;
  int row_distinct = -1;
  int distinct_idx = -1;
  for (int i = 0; i < n; ++i) {
    int first;
    cin >> first;
    result_xor ^= first;
    for (int j = 1; j < m; ++j) {
      int t;
      cin >> t;
      if (t != first) {
        row_distinct = i;
        distinct_idx = j;
      }
    }
  }

  if (result_xor != 0) {
    cout << "TAK\n";
    for (int i = 0; i < n; ++i) {
      cout << 1 << " ";
    }
    cout << "\n";
  } else if (result_xor == 0 && row_distinct != -1) {
    cout << "TAK\n";
    for (int i = 0; i < n; ++i) {
      if (row_distinct == i) {
        cout << distinct_idx + 1 << " ";
      } else {
        cout << 1 << " ";
      }
    }
    cout << "\n";
  } else {
    cout << "NIE\n";
  }
  return 0;
}
