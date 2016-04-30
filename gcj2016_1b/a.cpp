#include <iostream>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<char, string> > v;
vector<int> num;

map<char, int> mp;

void init_v() {
  v.push_back(make_pair('Z', "ZERO"));
  num.push_back(0);
  v.push_back(make_pair('W', "TWO"));
  num.push_back(2);
  v.push_back(make_pair('U', "FOUR"));
  num.push_back(4);
  v.push_back(make_pair('O', "ONE"));
  num.push_back(1);
  v.push_back(make_pair('R', "THREE"));
  num.push_back(3);
  v.push_back(make_pair('G', "EIGHT"));
  num.push_back(8);
  v.push_back(make_pair('F', "FIVE"));
  num.push_back(5);
  v.push_back(make_pair('X', "SIX"));
  num.push_back(6);
  v.push_back(make_pair('S', "SEVEN"));
  num.push_back(7);
  v.push_back(make_pair('N', "NINE"));
  num.push_back(9);
}

void solve(string s, int id) {
  vector<int> ans;
  for (int i = 0; i < s.length(); ++i) {
    mp[s[i]]++;
  }

  for (int i = 0; i < v.size(); ++i) {
    while (mp[v[i].first] > 0) {
      ans.push_back(num[i]);
      for (int j = 0; j < v[i].second.length(); ++j) {
        mp[v[i].second[j]]--;
      }
    }
  }

  sort(ans.begin(), ans.end());
  cout << "Case #" << id << ": ";
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  init_v();
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    solve(s, i + 1);
  }
  return 0;
}
