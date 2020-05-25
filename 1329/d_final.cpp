#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int P = 30;
string s;

void solve() {
  int n;
  cin >> s;
  n = s.length();
  vector<pair<int, int>> segs; // positions of same_letter segments.
  vector<int> cnt(P, 0);
  set<pair<int, int>> st;
  int sum_cnt = 0;
  for (int i = 0; i + 1 < n; ++i) {
    if (s[i] == s[i + 1]) {
      ++cnt[s[i] - 'a'];
      ++sum_cnt;
      segs.push_back({i + 1, s[i] - 'a'});
    }
  }

  for (int i = 0; i < P; ++i) {
    if (cnt[i]) {
      st.insert(make_pair(cnt[i], i));
    }
  }

  vector<pair<int, int>> segs_stack;
  vector<pair<int, int>> answer;
  int idx = 0;
  int cnt_removed = 0;

  auto on_remove_seg = [&](int symbol) {
    st.erase({cnt[symbol]--, symbol});
    st.insert({cnt[symbol], symbol});
  };

  auto apply_shift_for_seg = [](pair<int, int> &seg, int cnt_removed_left) {
    seg.first -= cnt_removed_left;
  };

  while (idx < segs.size() && st.rbegin()->first < sum_cnt - cnt[st.rbegin()->second]) {
    auto cur_seg = segs[idx++];
    apply_shift_for_seg(cur_seg, cnt_removed);
    if (segs_stack.empty()) {
      segs_stack.push_back(cur_seg);
    } else {
      if (segs_stack.back().second == cur_seg.second) {
        segs_stack.push_back(cur_seg);
      } else {
        // -1 because for pair (symbol, symbol) the end index is stored.
        answer.emplace_back(segs_stack.back().first, cur_seg.first - 1);
        // cout << "will remove now last: " << char(cur_seg.second + 'a') << " pos= " << cur_seg.first << ", back: " << char(segs_stack.back().second + 'a') << " pos= " << segs_stack.back().first << endl;
        cnt_removed += (cur_seg.first - segs_stack.back().first);

        on_remove_seg(cur_seg.second);
        on_remove_seg(segs_stack.back().second);
        sum_cnt -= 2;
        segs_stack.pop_back();
      }
    }
  }

  // Max cnt left is >= than sum of all the other segments.
  int major_symbol = st.rbegin()->second;
  while (idx < segs.size()) {
    auto cur_seg = segs[idx++];
    apply_shift_for_seg(cur_seg, cnt_removed);
    if (segs_stack.empty()) {
      segs_stack.push_back(cur_seg);
    } else {
      if ((cur_seg.second == major_symbol && segs_stack.back().second == major_symbol) ||
          (cur_seg.second != major_symbol && segs_stack.back().second != major_symbol)) {
        segs_stack.push_back(cur_seg);
      } else {
        answer.emplace_back(segs_stack.back().first, cur_seg.first - 1);
        cnt_removed += (cur_seg.first - segs_stack.back().first);
        segs_stack.pop_back();
      }
    }
  }

  // Only major could have been left
  while (!segs_stack.empty()) {
    answer.emplace_back(segs_stack.back().first, segs_stack.back().first);
    ++cnt_removed;
    segs_stack.pop_back();
  }

  printf("%d\n", (int)answer.size() + 1);
  for (auto el: answer) {
    printf("%d %d\n", el.first + 1, el.second + 1);
  }
  printf("1 %d\n", n - cnt_removed);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
