#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
bool used[MAXN];
vector<int> g[MAXN];

struct Res {
  long long overall_big_segments;
  int cnt_even_paths;
  int cnt_odd_paths;
  int subtree_size;
  Res()
    : overall_big_segments(0),
    cnt_even_paths(0),
    cnt_odd_paths(0),
    subtree_size(0)
  {};
};

// subtree size, number of pathes starting in this vertex
Res dfs(int v, long long &ans) {
  used[v] = true;

  Res res;
  vector<Res> subtree_results;
  long long sum_big_segments_subtr = 0;
  int sum_cnt_odd_paths_subtr = 0;
  for (auto to: g[v]) {
    if (!used[to]) {
      auto subtr_res = dfs(to, ans);
      res.subtree_size += subtr_res.subtree_size;
      subtree_results.push_back(subtr_res);

      res.cnt_even_paths += subtr_res.cnt_odd_paths;
      res.cnt_odd_paths += 1 + subtr_res.cnt_even_paths;
      res.overall_big_segments += subtr_res.overall_big_segments + subtr_res.cnt_odd_paths;

      sum_big_segments_subtr += subtr_res.overall_big_segments;
      sum_cnt_odd_paths_subtr += subtr_res.cnt_odd_paths;
    }
  }

  ans += res.overall_big_segments;
  ans += res.cnt_odd_paths;

  long long cnt_between_subtrs = 0;
  long long sum_paths_between_subtrs = 0;
  for (auto from_subtr: subtree_results) {
    // only even from -> even to
    cnt_between_subtrs += (from_subtr.subtree_size - from_subtr.cnt_odd_paths) * 1ll *
      (res.subtree_size - sum_cnt_odd_paths_subtr - (from_subtr.subtree_size - from_subtr.cnt_odd_paths));

    // odd from -> even to
    ans +=(from_subtr.cnt_odd_paths) * 1ll *
        (res.subtree_size - sum_cnt_odd_paths_subtr - (from_subtr.subtree_size - from_subtr.cnt_odd_paths));
    ans +=
      from_subtr.subtree_size * 1ll * (sum_big_segments_subtr - from_subtr.overall_big_segments);
    ans +=
      from_subtr.subtree_size * 1ll * (sum_cnt_odd_paths_subtr - from_subtr.cnt_odd_paths);
  }
  ans += cnt_between_subtrs / 2;
  res.subtree_size++;
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  long long ans = 0;
  dfs(0, ans);
  cout << ans << "\n";
  return 0;
}
