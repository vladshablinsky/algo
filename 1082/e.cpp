#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

int get_max_segment_sum(const vector<int> &v) {
  int cur_min = 0;
  int cur_sum = 0;
  int ans = 0;
  for (int i = 0; i < v.size(); ++i) {
    cur_sum += v[i];
    ans = max(ans, cur_sum - cur_min);
    cur_min = min(cur_min, cur_sum);
  }
  return ans;
}

int main() {
  int n, c;
  vector<int> v;
  vector<int> pref;
  unordered_map<int, vector<int>> mp;
  cin >> n >> c;
  v.resize(n);
  pref.resize(n);

  int cur_c = 0;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    if (v[i] == c) {
      ++cur_c;
    } else {
      mp[v[i]].push_back(i);
    }
    pref[i] = cur_c;
  }

  auto cnt = [&pref](int l, int r) {
    return pref[r] - (l > 0 ? pref[l - 1]: 0);
  };

  int res = 0;
  for (auto el: mp) {
    const auto &el_idx = el.second;
    vector<int> cnt_v;
    for(int i = 0; i + 1 < el_idx.size(); ++i) {
      cnt_v.push_back(1);
      cnt_v.push_back(-cnt(el_idx[i], el_idx[i + 1]));
    }
    cnt_v.push_back(1);
    cnt_v.push_back(-cnt(el_idx.back(), n - 1));
    res = max(res, get_max_segment_sum(cnt_v));
  }

  cout << cnt(0, n - 1) + res << "\n";
  return 0;
}
