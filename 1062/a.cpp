#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unordered_set>

using namespace std;


int main() {
  int n;
  int ans = 0;
  vector<int> v;
  cin >> n;
  int cur_ans = 0;
  int prev = -1;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    v.push_back(t);
    if (t - 1 == prev) {
      ++cur_ans;
    } else {
      ans = max(ans, cur_ans - 1);
      cur_ans = 0;
    }
    prev = t;
  }

  if (v.back() == 1000) {
    ans = max(ans, cur_ans);
  }

  cur_ans = 0;
  prev = 1e5;
  for (int i = n - 1; i >= 0; --i) {
    if (v[i] + 1 == prev) {
      ++cur_ans;
    } else {
      ans = max(ans, cur_ans - 1);
      cur_ans = 0;
    }
    prev = v[i];
  }

  if (v[0] == 1) {
    ans = max(ans, cur_ans);
  }

  cout << ans << "\n";
  return 0;
}
