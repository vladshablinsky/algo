#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<int, int> odd_poses_cnt;
unordered_map<int, int> even_poses_cnt;


int main() {
  int pref_xor = 0;
  long long ans = 0;
  int n;
  cin >> n;
  odd_poses_cnt[0] = 1;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    pref_xor ^= t;
    if (i % 2) {
      ans += odd_poses_cnt[pref_xor];
      odd_poses_cnt[pref_xor]++;
    } else {
      ans += even_poses_cnt[pref_xor];
      even_poses_cnt[pref_xor]++;
    }
  }
  cout << ans << "\n";
  return 0;
}
