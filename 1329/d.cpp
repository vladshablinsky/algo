#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

const int MAXN = 200005;
string s;

int t[MAXN];

int sum(int r) {
  int ans = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) {
    ans += t[r];
  }
  return ans;
}

void inc(int i, int val) {
  for (; i < MAXN; i = (i | (i + 1))) {
    t[i] += val;
  }
}

void init() {
  std::fill(t, t + MAXN, 0);
}

void solve() {
  init();
  cin >> s;
  list<pair<int, int>> segments;
  vector<pair<int, int>> ans;
  char prev_symbol = s[0];
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == prev_symbol) {
      segments.emplace_back(i, i);
    } else {
      segments.back().second = i;
    }
    prev_symbol = s[i];
  }

  auto print_segments = [](decltype(segments) &lst) {
    for (auto el: lst) {
      cout << "(" << el.first << ", " << el.second <<  ")";
    }
    cout << endl;
  };

  auto remove_and_merge_neighbours = [](decltype(segments) &lst, decltype(segments.begin()) &it) {
    auto result_it = next(it);
    if (it != lst.begin() && next(it) != lst.end() &&
        s[prev(it)->second] != s[next(it)->first]) {
      result_it = prev(it);
      prev(it)->second = next(it)->second;
      lst.erase(next(it));
    }
    lst.erase(it);
    return result_it;
  };

  auto add_to_ans = [](decltype(ans) &ans, pair<int, int> seg) {
    int segment_l = seg.first;
    int segment_r = seg.second;
    int removed_between = sum(segment_r) - sum(segment_l);
    int segment_len = segment_r - segment_l + 1 - removed_between;
    ans.push_back({segment_l - sum(segment_l), segment_r - sum(segment_r)});
    inc(segment_l, segment_len);
  };

  auto cur_it = segments.begin();
  while (cur_it != segments.end()) {
    if (cur_it == segments.begin()) {
      cur_it = next(cur_it);
    } else {
      if (s[cur_it->first] == s[cur_it->second]) {
        cur_it = next(cur_it);
      } else {
        add_to_ans(ans, *cur_it);
        cur_it = remove_and_merge_neighbours(segments, cur_it);
      }
    }
  }

  for (auto el: segments) {
    add_to_ans(ans, el);
  }
  //ans += segments.size();

  printf("%d\n", (int)ans.size());
  for (auto el: ans) {
    printf("%d %d\n", el.first + 1, el.second + 1);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
