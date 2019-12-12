#include <iostream>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<char, vector<int>> l;
unordered_map<char, vector<int>> r;

int main() {
  int n;
  scanf("%d", &n);

  string sl, sr;
  cin >> sl;
  cin >> sr;

  for (int i = 0; i < n; ++i) {
    l[sl[i]].push_back(i + 1);
    r[sr[i]].push_back(i + 1);
  }

  vector<int> left_l;
  vector<int> left_r;
  vector<pair<int, int>> ans;
  for (char c = 'a'; c <= 'z'; ++c) {
    while (l[c].size() && r[c].size()) {
      ans.push_back({l[c].back(), r[c].back()});
      l[c].pop_back();
      r[c].pop_back();
    }
    left_l.insert(left_l.end(), l[c].begin(), l[c].end());
    left_r.insert(left_r.end(), r[c].begin(), r[c].end());
  }

  auto &l_q = l['?'];
  auto &r_q = r['?'];
  while (left_l.size() && r_q.size()) {
    ans.push_back({left_l.back(), r_q.back()});
    left_l.pop_back();
    r_q.pop_back();
  }
  while (left_r.size() && l_q.size()) {
    ans.push_back({l_q.back(), left_r.back()});
    left_r.pop_back();
    l_q.pop_back();
  }

  while (l_q.size() && r_q.size()) {
    ans.push_back({l_q.back(), r_q.back()});
    l_q.pop_back();
    r_q.pop_back();
  }

  cout << ans.size() << "\n";
  for (auto &el: ans) {
    cout << el.first << " " << el.second << "\n";
  }
  return 0;
}
