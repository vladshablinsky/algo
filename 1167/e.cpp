#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 1000005;
const int INF = 1e9;
const int NONE = -1;
int first[MAX_N];
int last[MAX_N];
bool numbers[MAX_N];

int main() {
  int n, x;
  cin >> n >> x;

  first[x + 1] = last[x + 1] = n + 1;
  numbers[x + 1] = numbers[0] = true;
  for (int i = 0; i < n; ++i) {
    int cur_num;
    cin >> cur_num;
    if (!first[cur_num]) {
      first[cur_num] = i + 1;
    }
    last[cur_num] = i + 1;
    numbers[cur_num] = true;
  }

  int pref = 0;
  auto add_after = [&]() {
    if (!numbers[pref + 1]) {
      first[pref + 1] = last[pref + 1] = last[pref];
    }
    return true;
  };
  while (add_after() && pref + 1 <= x && last[pref] <= first[pref + 1]) {
    ++pref;
  }

  long long ans = 0;
  int cur_r = x + 1;
  auto add_before = [&]() {
    if (!numbers[cur_r - 1]) {
      first[cur_r - 1] = last[cur_r - 1] = first[cur_r];
    }
    return true;
  };
  for (int cur_l = pref; cur_l >= 0; --cur_l) {
    while (add_before() &&
        cur_l < cur_r - 1 &&
        last[cur_l] <= first[cur_r - 1] &&
        last[cur_r - 1] <= first[cur_r]) {
      --cur_r;
    }
    ans += (x + 1 - max(cur_l + 1, cur_r - 1));
  }

  cout << ans << "\n";
  return 0;
}
