#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<int> kmp(string s) {
  vector<int> ans(s.length());
  ans[0] = 0;
  for (int i = 1; i < s.length(); ++i) {
    int cur_pref = ans[i - 1];
    while (s[i] != s[cur_pref] && cur_pref > 0) {
      cur_pref = ans[cur_pref - 1];
    }
    if (s[i] == s[cur_pref]) {
      cur_pref++;
    }
    ans[i] = cur_pref;
  }
  return ans;
}

int main() {
  string s, t;
  cin >> s;
  cin >> t;
  int shift = kmp(t).back();
  //cout << "shift = " << shift << endl;
  int target_len = t.length() - shift;

  int cnt_free_zeros = 0;
  int cnt_free_ones = 0;
  for (auto c: s) {
    cnt_free_zeros += c == '0';
    cnt_free_ones += c == '1';
  }

  for (auto c: t) {
    cnt_free_zeros -= c == '0';
    cnt_free_ones -= c == '1';
    if (cnt_free_zeros < 0 || cnt_free_ones < 0) {
      cout << s << "\n";
      return 0;
    }
  }

  string ans = t;
  int cur_idx = 0;
  while (cnt_free_zeros >= int(t[shift + cur_idx % target_len] == '0') &&
      cnt_free_ones >= int(t[shift + cur_idx % target_len] == '1')) {
    ans.push_back(t[shift + cur_idx % target_len]);
    cnt_free_zeros -= t[shift + cur_idx % target_len] == '0';
    cnt_free_ones -= t[shift + cur_idx % target_len] == '1';
    ++cur_idx;
  }

  for (int i = 0; i < cnt_free_zeros; ++i) {
    ans.push_back('0');
  }
  for (int i = 0; i < cnt_free_ones; ++i) {
    ans.push_back('1');
  }
  cout << ans << "\n";
  return 0;
}
