#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

void solve() {
  int n;
  int cur_max;
  int cur_to_insert = 1;
  bool possible = true;
  vector<int> ans;
  vector<bool> used(n + 1, false);

  scanf("%d", &n);
  scanf("%d", &cur_max);

  ans.push_back(cur_max);
  used[cur_max] = true;

  auto insert_to_size = [&](int sz, int bound) {
    while (possible && ans.size() != sz) {
      if (cur_to_insert >= bound) {
        possible = false;
        break;
      } else {
        if (!used[cur_to_insert]) {
          ans.push_back(cur_to_insert);
          used[cur_to_insert] = true;
        }
        ++cur_to_insert;
      }
    }
  };

  for (int i = 1; i < n; ++i) {
    int next_max;
    scanf("%d", &next_max);
    if (next_max > cur_max) {
      insert_to_size(i, next_max);
      ans.push_back(next_max);
      cur_max = next_max;
    } else {
      insert_to_size(i + 1, cur_max);
    }
  }

  if (possible) {
    for (auto &el: ans) {
      printf("%d ", el);
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
