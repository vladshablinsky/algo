#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 100005;

int w[MAXN];
vector<int> g[MAXN];
int n, l;
long long s;

pair<int, pair<long long, int>> dfs(int v, int depth,
    long long sum_w_path, set<pair<long long, int>> &pref_sums) {
  pair<int, pair<long long, int>> ans;
  ans.first = 0;
  if (g[v].empty()) {
    return {1, {w[v], 1}};
  }

  pref_sums.insert({sum_w_path, depth});
  int lowest = depth + 1;

  for (auto to: g[v]) {
    auto res = dfs(to, depth + 1, sum_w_path + w[v], pref_sums);
    ans.first += res.first;
    long long sum_best_path_to = res.second.first;
    int length_best_path_to = res.second.second;

    // skip pathes that cannot be extended.
    if (length_best_path_to == l) {
      continue;
    }

    // Find lowest vertex so that sum_best_path_to + <some path up> <= s
    // this is equal to finding:
    //    sum_best_path_to + (sum_w_path - pref_sums[k]) <= s, where
    // k is as small as possible if pref_sums sorted ascendingly.
    // Use lower bound for that.
    auto it = pref_sums.lower_bound({sum_best_path_to + sum_w_path + w[v] - s, -1});
    if (it != pref_sums.end()) {
      int cnt_can_add = min(l - length_best_path_to, (depth - it->second + 1));
      if (depth + 1 - cnt_can_add < lowest) {
        lowest = depth + 1 - cnt_can_add;
        ans.second.first = sum_best_path_to + w[v];
        ans.second.second = length_best_path_to + 1;
      }
    }
  }

  if (lowest == depth + 1) {
    ans.first++;
    ans.second = {w[v], 1};
  }
  pref_sums.erase({sum_w_path, depth});
  return ans;
}

int main() {
  cin >> n >> l >> s;
  bool terminate = false;
  for (int i = 0; i < n; ++i) {
    cin >> w[i];
    if (w[i] > s) {
      terminate = true;
    }
  }
  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    g[p - 1].push_back(i);
  }

  if (terminate) {
    cout << "-1\n";
    return 0;
  }

  set<pair<long long, int>> pref_sums;
  cout << dfs(0, 0, 0, pref_sums).first << "\n";
  return 0;
}
