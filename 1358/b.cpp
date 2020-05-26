#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  map<int, int> mp;
  for (int i = 0; i < n; ++i) {
    int a_i;
    scanf("%d", &a_i);
    mp[a_i]++;
  }

  int cur_grannies = 1;
  int ans = 0;
  int buffer = 0;
  for (auto el: mp) {
    //cout << "el: " << el.first <<", " << el.second << endl;
    if (cur_grannies + buffer + el.second - 1 >= el.first) {
      cur_grannies += buffer + el.second;
      buffer = 0;
    } else {
      buffer += el.second;
    }
  }
  printf("%d\n", cur_grannies);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
