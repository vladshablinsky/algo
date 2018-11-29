#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <cstdlib>
#include <unordered_map>
#include <algorithm>
#include <list>

using namespace std;

int main() {
  vector<multiset<int, std::greater<int>>> v;
  unordered_map<int, int> mp; // s, cur_sum
  int n, m;
  cin >> n >> m;
  v.resize(m);
  for (int i = 0; i < n; ++i) {
    int s, r;
    cin >> s >> r;
    v[s - 1].insert(r);
  }

  for (int i = 0; i < m; ++i) {
    mp[i] = 0;
  }

  int ans = 0;
  while (!mp.empty()) {
    int cur_sum = 0;
    vector<int> avail_keys;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
      int s = it->first;
      avail_keys.push_back(s);
      mp[s] += *v[s].begin();
      v[s].erase(v[s].begin());
      if (mp[s] > 0) {
        cur_sum += mp[s];
      }
    }

    for (int key: avail_keys) {
      if (v[key].empty()) {
        mp.erase(key);
      }
    }

    ans = max(ans, cur_sum);
  }

  cout << ans << "\n";
  return 0;
}
