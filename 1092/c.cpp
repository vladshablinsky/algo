#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

using namespace std;

const int MAXN = 105;

int main() {
  int n;
  cin >> n;
  vector<string> v;
  vector<bool> found_pref(n - 1, false);

  string pref, suff;
  for (int i = 0; i < 2 * n - 2; ++i) {
    string cur_s;
    cin >> cur_s;
    if (cur_s.length() == n - 1) {
      if (pref.length()) {
        suff = cur_s;
      } else {
        pref = cur_s;
      }
    }
    v.emplace_back(std::move(cur_s));
  }

  auto check_same = [](string &a, string &b, bool reverse=false) {
    for (int i = 0; i < a.length(); ++i) {
      if (a[i] != b[i + reverse * (b.length() - a.length())]) {
        return false;
      }
    }
    return true;
  };

  string ans;
  auto gen_ans = [&]() {
    fill(found_pref.begin(), found_pref.end(), false);
    for (auto &el: v) {
      if (check_same(el, pref) && !found_pref[el.size() - 1]) {
        found_pref[el.size() - 1] = true;
        ans.push_back('P');
      } else if (check_same(el, suff, true)) {
        ans.push_back('S');
      } else {
        ans.clear();
        return;
      }
    }
  };

  gen_ans();
  if (ans.empty()) {
    swap(pref, suff);
    gen_ans();
  }

  cout << ans << "\n";
  return 0;
}
