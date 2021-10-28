#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

long long solve() {
  int n;
  scanf("%d", &n);

  vector<long long> cnt_level(n, 0ll);
  vector<long long> cnt_topic(n, 0ll);
  vector<pair<int, int>> problems;

  int topic, level;
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &topic, &level);
    --topic;
    --level;
    cnt_level[level]++;
    cnt_topic[topic]++;
    problems.emplace_back(topic, level);
  }

  long long cnt_bad = 0;
  for (auto [tpc, lvl]: problems) {
    cnt_bad += (cnt_level[lvl] - 1) * (cnt_topic[tpc] - 1);
  }

  return n * 1ll * (n - 1) * (n - 2) / 6 - cnt_bad;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%lld\n", solve());
  }
}
