#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5005;
pair<int, int> segments[MAXN];
int cnt_painters[MAXN];
int cnt_ones[MAXN];
int cnt_twos[MAXN];

int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    segments[i] = {l, r};
    cnt_painters[l]++;
    cnt_painters[r + 1]--;
  }

  int cur_cnt = 0;
  int max_painted = 0;
  for (int i = 1; i <= n; ++i) {
    cur_cnt += cnt_painters[i];
    cnt_ones[i] = cnt_ones[i - 1] + (cur_cnt == 1);
    cnt_twos[i] = cnt_twos[i - 1] + (cur_cnt == 2);
    max_painted += (cur_cnt != 0);
  }

  int min_remove = max_painted;
  for (int i = 0; i + 1 < q; ++i) {
    for (int j = i + 1; j < q; ++j) {
      int cur_remove = 0;
      auto s1 = segments[i];
      auto s2 = segments[j];
      if (s1.first > s2.first) {
        swap(s1, s2);
      }

      if (s1.second < s2.first) {
        cur_remove += cnt_ones[s1.second] - cnt_ones[s1.first - 1];
        cur_remove += cnt_ones[s2.second] - cnt_ones[s2.first - 1];
      } else {  // s1.second >= s2.first
        cur_remove += cnt_ones[s2.first - 1] - cnt_ones[s1.first - 1];
        cur_remove += cnt_ones[max(s1.second, s2.second)] - cnt_ones[min(s1.second, s2.second)];
        cur_remove += cnt_twos[min(s1.second, s2.second)] - cnt_twos[s2.first - 1];
      }
      min_remove = min(min_remove, cur_remove);
    }
  }

  cout << max_painted - min_remove << "\n";
  return 0;
}
