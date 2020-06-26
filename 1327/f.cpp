#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 500005;
const int MOD = 998244353;

int n, k, m;

inline int modmul(int a, int b) {
  return (a * 1ll * b) % MOD;
}

inline int modadd(int a, int b) {
  return (a + b) % MOD;
}

// ranges[r] -- sorted descendingly by set pairs (l, x)
pair<pair<int, int>, int> ranges[MAXN];

int solve_for_bit(int bit_id) {
  //cout << "bit_id: " << bit_id << endl;
  vector<int> cnt_set_bits_on_range(n + 2, 0);
  vector<int> max_l_ending_at(n + 2, 0);

  // position g(i) -- mostleft position that there is no zero-segments from it to i.
  vector<int> g(n + 2, 0);

  for (int i = 1; i <= m; ++i) {
    int l = ranges[i].first.first;
    int r = ranges[i].first.second;
    bool is_set = ((ranges[i].second & (1 << bit_id)) != 0);

    if (is_set) {
      cnt_set_bits_on_range[l]++;
      cnt_set_bits_on_range[r + 1]--;
    } else {
      max_l_ending_at[r] = max(max_l_ending_at[r], l);
    }
  }

  // cout << "ml: {";
  // for (int i = 1; i <= n + 1; ++i) {
  //   cout << max_l_ending_at[i] << ", ";
  // }
  // cout << "}\n";

  // transform to whether i'th bit is 1.
  int cur_set_bits = 0;
  int cur_g = 0;
  //cout << "g: {";
  for (int i = 1; i <= n + 1; ++i) {
    cur_set_bits += cnt_set_bits_on_range[i];
    cnt_set_bits_on_range[i] = (cur_set_bits > 0);
    g[i] = cur_g;
    cur_g = max(cur_g, max_l_ending_at[i]);
    //cout << g[i] << ", ";
  }
  //cout << "}\n";

  // f(i) -- number of ways to set first i els so that i'th el is zero and
  // zero-range condition satisfied for all ranges to the left
  vector<int> f(n + 2, 1);
  vector<int> pref_f(n + 2, 1);
  for (int i = 1; i <= n + 1; ++i) {
    if (cnt_set_bits_on_range[i]) {
      f[i] = 0;
    } else {
      f[i] = (pref_f[i - 1] - (g[i] ? pref_f[g[i] - 1] : 0) + MOD) % MOD;
    }
    pref_f[i] = modadd(pref_f[i - 1], f[i]);
  }
  return f[n + 1];
}

int main() {
  scanf("%d%d%d", &n, &k, &m);

  for (int i = 1; i <= m; ++i) {
    scanf(
      "%d%d%d",
      &ranges[i].first.first,
      &ranges[i].first.second,
      &ranges[i].second
    );
  }
  ranges[0] = {{0, 0}, 0};

  int ans = 1;
  for (int i = 0; i < k; ++i) {
    ans = modmul(ans, solve_for_bit(i));
  }
  printf("%d\n", ans);

  return 0;
}
