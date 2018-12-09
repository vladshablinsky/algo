#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
  int n;
  bool skip = false;
  vector<pair<int, int>> v;
  vector<pair<int, int>> res;
  vector<int> cnt_min;
  set<int> st;
  cin >> n;
  cnt_min = vector<int>(n + 1, 0);
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    v.push_back({x, y});
    if (max(x, y) != n || x == y) {
      skip = true;
    }
    cnt_min[min(x, y)]++;
  }
  for (int i = 1; i <= n - 1; ++i) {
    if (!cnt_min[i]) {
      st.insert(i);
    }
  }

  if (skip) {
    cout << "NO\n";
    return 0;
  }


  for (int i = 1; i <= n - 1; ++i) {
    if (cnt_min[i] == 0) {
      continue;
    }

    int to_add = cnt_min[i] - 1;
    int prev = n;
    while (to_add && st.size() >= to_add && *st.begin() < i) {
      res.push_back({prev, *st.begin()});
      prev = *st.begin();
      st.erase(st.begin());
      --to_add;
    }

    if (to_add) {
      skip = true;
      break;
    }
    res.push_back({prev, i});
  }

  if (skip) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    for (auto el: res) {
      cout << el.first << " " << el.second << "\n";
    }
  }

  return 0;
}
