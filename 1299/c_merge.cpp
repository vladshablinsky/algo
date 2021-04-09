#include <iostream>
#include <cstdio>
#include <vector>
#include <list>

using namespace std;

const int MAXN = 1000005;
int a[MAXN];

int main() {
  int n;
  list<pair<double, int>> v;

  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    v.push_back({t, 1});
  }

  auto cur_it = prev(v.end());
  while (true) {
    auto next_it = next(cur_it);
    while (next_it != v.end() &&
        (next_it->first + cur_it->first) / (next_it->second + cur_it->second) <
        cur_it->first / cur_it->second) {
      cur_it->first += next_it->first;
      cur_it->second += next_it->second;
      v.erase(next_it);
      next_it = next(cur_it);
    }
    if (cur_it == v.begin()) {
      break;
    }
    cur_it--;
  }

  for (auto &el: v) {
    for (int i = 0; i < el.second; ++i) {
      printf("%.8f ", el.first / el.second);
    }
  }
  return 0;
}
