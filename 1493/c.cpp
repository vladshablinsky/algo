#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

string solve() {
  vector<int> cnt('z' - 'a' + 1, 0);
  string s;
  int n, k;

  cin >> n >> k;
  cin >> s;

  long long required_to_beautiful = 0;
  for (auto c: s) {
    cnt[c - 'a']++;
    cnt[c - 'a'] %= k;
  }

  for (auto el: cnt) {
    if (el) {
      required_to_beautiful += (k - el);
    }
  }
  if (!required_to_beautiful) {
    return s;
  }

  auto add_cnt = [&](char c, int to_add) {
    auto& cnt_c = cnt[c - 'a'];
    required_to_beautiful -= (k - cnt_c) * (cnt_c != 0);
    cnt_c = (cnt_c + to_add + k) % k;
    required_to_beautiful += (k - cnt_c) * (cnt_c != 0);
  };

  for (int i = n - 1; i >= 0; --i) {
    add_cnt(s[i], -1);
    for (char lexi_next = s[i] + 1; lexi_next <= 'z'; ++lexi_next) {
      add_cnt(lexi_next, 1);

      long long remainder = -required_to_beautiful + n - i - 1;
      if (remainder >= 0 && (remainder % k) == 0) {
        s[i] = lexi_next;
        int j = i + 1;
        while (remainder--) {
          s[j++] = 'a';
        }
        for (int c_i = 0; c_i < cnt.size(); ++c_i) {
          int to_add = (k - cnt[c_i]) * (cnt[c_i] != 0);
          while (to_add--) {
            s[j++] = c_i + 'a';
          }
        }
        return s;
      }
      add_cnt(lexi_next, -1);
    }
  }

  return "-1";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
