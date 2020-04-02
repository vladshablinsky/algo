#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  map<pair<int, int>, int> mp;
  for (int i = 0; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    if (a > b) {
      swap(a, b);
    }
    mp[{a, b}] = i + 1;
  }

  vector<int> ans(n);
  auto try_fill = [](int n, vector<int> &ans, map<pair<int, int>, int> &mp) {
    int prev = ans[0];
    int prev_prev = ans[1];
    for (int i = 0; i < n; ++i) {
      int idx = (i + 3) % n;
      pair<int, int> key = {prev, prev_prev};
      if (prev > prev_prev) {
        swap(key.first, key.second);
      }
      if (mp.count(key)) {
        ans[idx] = mp[key];
        prev_prev = prev;
        prev = ans[idx];
      } else {
        return false;
      }
    }
    return true;
  };
  ans[0] = mp.begin()->first.first;
  ans[1] = mp.begin()->first.second;
  if (!try_fill(n, ans, mp)) {
    swap(ans[0], ans[1]);
    try_fill(n, ans, mp);
  }

  for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
    cout << *it << " ";
  }
  cout << "\n";
  return 0;
}
