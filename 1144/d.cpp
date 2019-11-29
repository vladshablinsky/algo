#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>

using namespace std;

const int MAXN = 200005;

int cnt_el[MAXN];
int a[MAXN];

int main() {
  int n;
  scanf("%d", &n);

  int max_cnt = 0;
  int el = 0;

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    ++cnt_el[a[i]];

    if (cnt_el[a[i]] > max_cnt) {
      max_cnt = cnt_el[a[i]];
      el = a[i];
    }
  }

  vector<int> to_process;
  for (int i = 0; i < n; ++i) {
    if (a[i] == el) {
      to_process.push_back(i);
    }
  }

  vector<tuple<int, int, int>> ans;
  while (!to_process.empty()) {
    int cur_idx = to_process.back();
    to_process.pop_back();

    if (cur_idx + 1 < n && a[cur_idx + 1] != el) {
      int t = 1;
      if (a[cur_idx + 1] > el) {
        t = 2;
      }
      ans.push_back(make_tuple(t, cur_idx + 1, cur_idx));
      a[cur_idx + 1] = el;
      to_process.push_back(cur_idx + 1);
    }

    if (cur_idx - 1 >= 0 && a[cur_idx - 1] != el) {
      int t = 1;
      if (a[cur_idx - 1] > el) {
        t = 2;
      }
      ans.push_back(make_tuple(t, cur_idx - 1, cur_idx));
      a[cur_idx - 1] = el;
      to_process.push_back(cur_idx - 1);
    }
  }

  printf("%d\n", int(ans.size()));
  for (auto &el: ans) {
    int t, i, j;
    std::tie(t, i, j) = el;
    printf("%d %d %d\n", t, i + 1, j + 1);
  }
  return 0;
}
