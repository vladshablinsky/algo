#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto &el: v) {
    cin >> el;
  }
  sort(v.begin(), v.end());

  vector<int> any_order;
  bool care_prefix = true;
  int print_i = 0;
  for (int i = 0; i < n; ++i) {
    if (care_prefix && v[i] == print_i) {
      while (i + 1 < n && v[i] == v[i + 1]) {
        ++i;
        any_order.push_back(v[i]);
      }
      cout << v[i] << " ";
      print_i++;
    } else {
      care_prefix = false;
      cout << v[i] << " ";
    }
  }
  for (auto el: any_order) {
    cout << el << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
