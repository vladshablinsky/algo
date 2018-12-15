#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void solve(string &s) {
  map<char, int> mp;
  for (char c: s) {
    mp[c]++;
  }
  if (mp.size() == 1) {
    cout << "-1\n";
  } else {
    string res;
    for (auto el: mp) {
      for (int j = 0; j < el.second; ++j) {
        res.push_back(el.first);
      }
    }
    cout << res << "\n";
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}
