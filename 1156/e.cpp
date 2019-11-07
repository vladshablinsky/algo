#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200005;
int a[MAX_N];
int idx_map[MAX_N];

int rec(int l, int r, set<pair<int, int>, std::greater<pair<int, int>>> &st) {
  if (st.empty()) {
    return 0;
  }
  int cur_ans = 0;
  int mx = st.begin()->first;
  int idx = st.begin()->second;
  st.erase(st.begin());

  set<pair<int, int>, std::greater<pair<int, int>>> other_st;
  if (idx - l < r - idx) {
    for (int i = l; i < idx; ++i) {
      other_st.insert({a[i], i});
      st.erase({a[i], i});
    }
    for (auto el: other_st) {
      auto to_find = make_pair(mx - el.first, idx_map[mx - el.first]);
      if (st.count(to_find)) {
        ++cur_ans;
      }
    }
    return cur_ans + rec(l, idx - 1, other_st) + rec(idx + 1, r, st);
  } else {
    for (int i = r; i > idx; --i) {
      other_st.insert({a[i], i});
      st.erase({a[i], i});
    }
    for (auto el: other_st) {
      auto to_find = make_pair(mx - el.first, idx_map[mx - el.first]);
      if (st.count(to_find)) {
        ++cur_ans;
      }
    }
    return cur_ans + rec(l, idx - 1, st) + rec(idx + 1, r, other_st);
  }
}

int main() {
  int n;
  set<pair<int, int>, std::greater<pair<int, int>>> st;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    idx_map[a[i]] = i;
    st.insert({a[i], i});
  }

  cout << rec(0, n - 1, st) << "\n";
  return 0;
}
