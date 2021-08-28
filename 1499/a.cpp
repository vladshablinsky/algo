#include <iostream>

using namespace std;

bool can_place(int cells_cnt, int cnt) {
  if (cnt * 2 == cells_cnt) {
    return cells_cnt % 2 == 0;
  }
  return cells_cnt > cnt * 2;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k1, k2, w, b;
    cin >> n >> k1 >> k2 >> w >> b;
    int sum = k1 + k2;
    if (can_place(sum, w) && can_place(2 * n - sum, b)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
