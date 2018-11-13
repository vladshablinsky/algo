#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
  unordered_map<int, int> mp;
  int n;
  cin >> n;

  int max_power = 1;
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    if (n % i == 0) {
      while(n % i == 0) {
        mp[i]++;
        n /= i;
      }
      result *= i;
      max_power = max(max_power, mp[i]);
    }
  }

  bool all_max_power = true;
  bool max_power_power_two = (max_power && !(max_power & (max_power - 1)));
  for (auto x: mp) {
    if (x.second != max_power) {
      all_max_power = false;
      break;
    }
  }

  int cnt_sqr = 0;
  if (max_power > 1) {
    while ((1 << cnt_sqr) < max_power) {
      ++cnt_sqr;
    }
  }

  if (!all_max_power) {
    ++cnt_sqr;
  } else if (!max_power_power_two) {
    ++cnt_sqr;
  }

  cout << result << " " << cnt_sqr << "\n";
  return 0;
}
