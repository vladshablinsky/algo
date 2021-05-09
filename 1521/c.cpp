#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;


void solve() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  unordered_map<int, int> mp;
  int n;
  cin >> n;

  // Initial phase.
  cout << "? " << 1 << " " << 1 << " " << 2 << " " << n - 1 << "\n";
  int max_1_2;
  int min_1_2;
  int num;
  cin >> max_1_2;
  cout << "? " << 1 << " " << 2 << " " << 1 << " " << n - 1 << "\n";
  cin >> num;
  max_1_2 = max(max_1_2, num);
  cout << "? " << 1 << " " << 2 << " " << 1 << " " << max_1_2 - 1 << "\n";
  cin >> num;

  // p1 < p2 => result is p2 - 1
  int cur_unknown_idx;
  int max_known = max_1_2;
  if (num == max_known - 1) {
    mp[max_known] = 2;
    cur_unknown_idx = 1;
  } else { // p1 > p2 otherwise.
    mp[max_known] = 1;
    cur_unknown_idx = 2;
  }

  // Get second
  cout << "? " << 2 << " " << cur_unknown_idx << " " << mp[max_known] << " " << 1 << "\n";
  cin >> min_1_2;
  if (min_1_2 == max(2, max_known)) {
    cout << "? " << 1 << " " << mp[max_known] << " " << cur_unknown_idx << " " << n - 1 << "\n";
    cin >> max_1_2;

    mp[max_1_2] = cur_unknown_idx;
    max_known = max(max_known, max_1_2);
  } else {
    mp[min_1_2] = cur_unknown_idx;
    max_known = max(max_known, min_1_2);
  }

  // The first and second are known.
  // find the others
  vector<int> indices;
  for (int i = 3; i <= n; ++i) {
    indices.push_back(i);
  }
  shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));

  for (int i = 3; i <= n; ++i) {
    // still don't know n - i + 1 numbers
    int cnt_less_unknown = max_known - (i - 1);
    int cnt_greater_unknown = n - max_known + 1;
    int idx = indices[i - 3];

    // chances are we'll encounter the number that is less!
    if (cnt_less_unknown > cnt_greater_unknown) {
      cout << "? 2 " << idx << " " << mp[max_known] << " " << 1 << endl;
      cin >> min_1_2;
      if (min_1_2 == max_known) { // ops, bad luck!
        cout << "? 1 " << mp[max_known] << " " << idx << " " << n - 1 << endl;
        cin >> max_1_2;
        mp[max_1_2] = idx;
        max_known = max(max_known, max_1_2);
      } else {
        mp[min_1_2] = idx;
      }
    } else { // chances are we'll encounter the number that is greater
      cout << "? 1 " << mp[max_known] << " " << idx << " " << n - 1 << endl;
      cin >> max_1_2;
      if (max_1_2 == min(max_known, n - 1)) {  // ops, bad luck!
        cout << "? 2 " << idx << " " << mp[max_known] << " " << 1 << endl;
        cin >> min_1_2;
        mp[min_1_2] = idx;
      } else {
        mp[max_1_2] = idx;
        max_known = max(max_known, max_1_2);
      }
    }
  }

  vector<int> ans(n, 0);
  for (auto [num, idx]: mp) {
    ans[idx - 1] = num;
  }
  cout << "! ";
  for (auto el: ans) {
    cout << el << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  cout.flush();
  return 0;
}
