#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n, k;
  vector<int> h;
  scanf("%d %d\n", &n, &k);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d ", &t);
    h.push_back(t);
  }

  sort(h.begin(), h.end());

  long long ans = 0;
  int cur_level_idx = n - 1;
  long long carry = 0;
  while (h[cur_level_idx] != h[0]) {
    long long diff_h = h[cur_level_idx] - h[cur_level_idx - 1];

    long long carry_reduced_h = carry / (n - cur_level_idx);
    if (carry_reduced_h > diff_h) {
      carry = carry - diff_h * (n - cur_level_idx);
    } else {
      carry = 0;
    }

    diff_h = max(0ll, diff_h - carry_reduced_h);
    if (!diff_h) {
      cur_level_idx--;
      continue;
    }

    long long cnt_layers_per_slice = k / (n - cur_level_idx);
    long long cnt_slices = (diff_h + cnt_layers_per_slice - 1) / cnt_layers_per_slice;
    ans += cnt_slices;
    long long to_be_filled_in_last_slice = diff_h * (n - cur_level_idx)
      - (cnt_slices - 1) * cnt_layers_per_slice * (n - cur_level_idx);
    carry = k - to_be_filled_in_last_slice;
    cur_level_idx--;
  }
  cout << ans << "\n";
  return 0;
}
