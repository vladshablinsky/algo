#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n, m;
  vector<int> v;
  cin >> n >> m;
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  sort(v.begin(), v.end());
  int cur_h = 1;
  long long ans = 0;
  int i;
  for (i = 0; i < n - 1; ++i) {
    ans += v[i] != 0 ? v[i] - 1 : 0;
    if (v[i] >= cur_h) {
      ++cur_h;
    }
  }

  if (cur_h - 1 == v[i]) {
    ans += v[i] != 0 ? v[i] - 1 : 0;
  } else {
    ans += (cur_h - 1);
  }
  cout << ans << "\n";
  return 0;
}
