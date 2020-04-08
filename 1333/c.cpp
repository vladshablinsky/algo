#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main() {
  int n;
  int cur_a;
  scanf("%d", &n);
  long long cur_sum = 0;
  map<long long, int> mp;
  mp[0] = -1;
  int last_zero_subarray_l = -1;
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &cur_a);
    cur_sum += cur_a;
    if (mp.count(cur_sum)) {
      last_zero_subarray_l = max(last_zero_subarray_l, mp[cur_sum] + 1);
    }
    ans += (i - last_zero_subarray_l);
    mp[cur_sum] = i;
  }
  cout << ans << "\n";
  return 0;
}
