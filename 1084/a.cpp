#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


int abs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int main() {
  int n;
  vector<int> v;
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  int ans = 1e9;
  int cur_floor = 1;
  for (int i = 1; i <= n; ++i) {
    int cur_ans = 0;
    for (int j = 1; j <= n; ++j) {
      cur_ans += v[j - 1] * 2 * (abs(i - j) + abs(j - 1) + abs(1 - i));
    }
    if (cur_ans < ans) {
      ans = cur_ans;
      cur_floor = i;
    }
  }
  cout << ans << endl;
  return 0;
}
