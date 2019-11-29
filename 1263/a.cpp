#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  long long ans = 0;
  vector<long long> v(3);
  cin >> v[0] >> v[1] >> v[2];
  sort(v.begin(), v.end());
  ans += v[0];
  v[1] -= v[0];
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
