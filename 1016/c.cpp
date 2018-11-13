#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
  vector<long long> v;
  vector<long long> pref_up_down_mul;
  vector<long long> pref_up_down;
  vector<long long> pref_down_up_mul;
  vector<long long> pref_down_up;

  int n;
  cin >> n;
  v.resize(2 * n);
  pref_up_down_mul.resize(2 * n);
  pref_down_up_mul.resize(2 * n);
  pref_up_down.resize(2 * n);
  pref_down_up.resize(2 * n);

  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> v[2 * n - i - 1];
  }

  for (int i = 0; i < 2 * n; ++i) {
    pref_up_down_mul[i] = (i ? pref_up_down_mul[i - 1] : 0) + v[i] * i;
    pref_up_down[i] = (i ? pref_up_down[i - 1] : 0) + v[i];
  }

  for (int i = 0; i < 2 * n; ++i) {
    pref_down_up_mul[i] = (i ? pref_down_up_mul[i - 1] : 0) + v[2 * n - 1 - i] * i;
    pref_down_up[i] = (i ? pref_down_up[i - 1] : 0) + v[2 * n - 1 - i];
  }

  long long ans = 0;
  long long step = 0;
  int down_idx = 0;
  int up_idx = 0;
  long long cur_zig_zag_sum = 0;

  long long cur_ans = 0;
  while (up_idx < n) {
    cur_ans = cur_zig_zag_sum;

    // cout << "1) up_idx: " << up_idx << ", down_idx: " << down_idx << endl;

    // now we're up
    long long loop_up_down_mul = pref_up_down_mul[2 * n - 1 - down_idx] -
      (up_idx ? pref_up_down_mul[up_idx - 1] : 0);

    long long loop_up_down = pref_up_down[2 * n - 1 - down_idx] -
      (up_idx ? pref_up_down[up_idx - 1] : 0);

    cur_ans += (loop_up_down_mul + (step - up_idx) * loop_up_down);

    // cout << "cur_zig_zag " << cur_zig_zag_sum << endl;
    // cout << "loop_up_down_mul " << loop_up_down_mul << endl;
    // cout << "loop_up_down " << loop_up_down << endl;

    // cout << "cur_ans: " << cur_ans << endl;
    ans = max(ans, cur_ans);

    cur_zig_zag_sum += v[up_idx++] * step++;
    cur_zig_zag_sum += v[2 * n - 1 - down_idx++] * step++;

    // cout << "2) up_idx: " << up_idx << ", down_idx: " << down_idx << endl;

    if (down_idx == n) {
      break;
    }

    cur_ans = cur_zig_zag_sum;

    // now we're down;
    long long loop_down_up_mul = pref_down_up_mul[2 * n - 1 - up_idx] -
      pref_down_up_mul[down_idx - 1];

    long long loop_down_up = pref_down_up[2 * n - 1 - up_idx] -
      pref_down_up[down_idx - 1];

    // cout << "cur_zig_zag " << cur_zig_zag_sum << endl;
    // cout << "loop_down_up_mul " << loop_down_up_mul << endl;
    // cout << "loop_down_up " << loop_down_up << endl;

    cur_ans += (loop_down_up_mul + (step - down_idx) * loop_down_up);

    // cout << "cur_ans: " << cur_ans << endl;
    ans = max(ans, cur_ans);

    cur_zig_zag_sum += v[2 * n - 1 - down_idx++] * step++;
    cur_zig_zag_sum += v[up_idx++] * step++;
  }

  cout << ans << "\n";
  return 0;
}
