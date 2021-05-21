#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int solve() {
  int n;
  cin >> n;

  vector<int>v(n);
  for (auto& el: v) {
    cin >> el;
  }

  bool sorted = true;
  for (int i = 0; i < n - 1; ++i) {
    if (v[i] > v[i + 1]) {
      sorted = false;
      break;
    }
  }

  if (sorted) {
    return 0;
  } else if (v.front() == 1 || v.back() == n) {
    return 1;
  } else if (v.front() == n && v.back() == 1) {
    return 3;
  } else {
    return 2;
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }

  return 0;
}
