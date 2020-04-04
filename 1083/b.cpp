#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main() {
  int n, k;
  long long ans = 0;
  string s, t;

  cin >> n >> k;
  cin >> s >> t;
  // f[j] at i'th iteration is
  //   -- max number of string we can get according to constraints
  //    (k included) so that j is a mask whether we already
  //    (got > s or not) * 2 + (got < t or not)
  vector<int> f_prev(4);
  vector<int> f_cur(4);


  f_prev[0] = 1;

  int cur_cnt_prefixes = 0;
  int cur_cnt_to_add = 2;
  for (int i = 0; i < n; ++i) {
    if (cur_cnt_prefixes < k) {
      f_cur[0] = f_prev[0] * (s[i] == t[i]);
      f_cur[1] = f_prev[1] + f_prev[0] * (s[i] == 'a' && t[i] == 'b'); // 'a' -> 'b'
      f_cur[2] = f_prev[2] + f_prev[0] * (s[i] == 'a' && t[i] == 'b'); // 'a' -> 'b'
      f_cur[3] = f_prev[3] * 2 + f_prev[1] * (s[i] == 'a') + f_prev[2] * (t[i] == 'b');

      int sum = f_cur[0] + f_cur[1] + f_cur[2] + f_cur[3];
      cur_cnt_prefixes = min(k, sum);
      swap(f_prev, f_cur);
    }
    ans += min(cur_cnt_prefixes, cur_cnt_to_add);
    if (cur_cnt_to_add * 2 > k) {
      cur_cnt_to_add = k;
    } else {
      cur_cnt_to_add *= 2;
    }
  }

  cout << ans << "\n";
  return 0;
}
