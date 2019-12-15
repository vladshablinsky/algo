#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 1505;

int a[MAXN];
unordered_map<int, vector<pair<int, int>>> mp;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int ans = 0;
  int sum_for_ans;
  for (int l = 0; l < n; ++l) {
    int cur_sum = 0;
    for (int r = l; r < n; ++r) {
      cur_sum += a[r];
      if (!mp.count(cur_sum) || mp[cur_sum].back().second < l) {
        mp[cur_sum].push_back({l, r});
      } else if (mp[cur_sum].back().second > r){
        mp[cur_sum].back() = make_pair(l, r);
      }
      if (mp[cur_sum].size() > ans) {
        ans = mp[cur_sum].size();
        sum_for_ans = cur_sum;
      }
    }
  }
  cout << mp[sum_for_ans].size() << "\n";
  for (auto &el: mp[sum_for_ans]) {
    cout << el.first + 1 << " " << el.second + 1 << "\n";
  }
  return 0;
}
