#include <iostream>
#include <map>
#include <string>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

map<string, int> mp;
vector<pair<int, string> > ans;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    mp[s] = i + 1;
  }
  for (map<string, int>::iterator it = mp.begin(); it != mp.end(); ++it) {
    ans.push_back(make_pair(it->second, it->first));
  }

  sort(ans.begin(), ans.end());
  for (int i = ans.size() - 1; i >= 0; --i) {
    cout << ans[i].second << "\n";
  }
  return 0;
}
