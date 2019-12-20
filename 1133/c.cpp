#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int K = 5;

int main() {
  int n;
  vector<int> v;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    v.push_back(t);
  }

  sort(v.begin(), v.end());

  int ans = 0;
  int l = 0;
  for (int r = 0; r < n; ++r) {
    while (l < r && v[r] - v[l] > K) {
      ++l;
    }
    ans = max(ans, r - l + 1);
  }
  cout << ans << "\n";
  return 0;
}
