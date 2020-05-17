#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void solve() {
  int n;
  long long l, r;
  cin >> n >> l >> r;
  long long left_to_print = r - l + 1;
  long long elements_passed = 0;
  for (
    int cnt_pairs = n - 1, start_vertex = 1;
    left_to_print && cnt_pairs > 0;
    --cnt_pairs, ++start_vertex
  ) {
    if (left_to_print && (l <= elements_passed + 2 * cnt_pairs && r >= elements_passed + 1)) {
      for (int i = 1; left_to_print && i <= 2 * cnt_pairs; ++i) {
        if (elements_passed + i >= l && elements_passed + i <= r) {
          --left_to_print;
          cout << (i & 1 ? start_vertex: start_vertex + (i + 1) / 2) << " ";
        }
      }
    }

    elements_passed += 2 * cnt_pairs;
  }

  if (left_to_print) {
    cout << 1;
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }

  return 0;
}
