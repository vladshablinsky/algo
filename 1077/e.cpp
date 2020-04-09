#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <ctime>

using namespace std;

const int MAXN = 200005;
const int MAX_CONTESTS = 19; // log MAXN
const int INF = 1e9;

struct custom_hash {
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    x ^= FIXED_RANDOM;
    return x ^ (x >> 16);
  }
};

int main() {
  int n;
  scanf("%d", &n);
  unordered_map<int, int, custom_hash> cnt;
  for (int i = 0; i < n; ++i) {
    int a_i;
    scanf("%d", &a_i);
    cnt[a_i]++;
  }

  vector<int> freqs;
  for (auto &el: cnt) {
    freqs.push_back(el.second);
  }
  sort(freqs.begin(), freqs.end());

  int ans = 0;
  for (int i = 0; i <= MAX_CONTESTS; ++i) {
    int cur_day = i;
    int x = INF;
    for (int j = (int)freqs.size() - 1; j >= 0 && cur_day >= 0; --j) {
      x = min(x, freqs[j] / (1 << cur_day));
      --cur_day;
    }
    if (cur_day == -1) {
      ans = max(ans, x * ((1 << (i + 1)) - 1));
    }
  }
  printf("%d\n", ans);
  return 0;
}

