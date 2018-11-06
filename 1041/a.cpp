#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  int ans = 0;
  sort(v.begin(), v.end());
  for (int i = 1; i < n; ++i) {
    ans += (v[i] - 1 - v[i - 1]);
  }
  cout << ans << "\n";
  return 0;
}
