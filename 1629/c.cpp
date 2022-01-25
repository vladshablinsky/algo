#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);

  vector<queue<int>> idx(n + 1);
  vector<int> result;


  for (int i = 0, el; i < n; ++i) {
    scanf("%d", &el);
    idx[el].push(i);
  }

  int l = 0;
  while (l < n) {
    int cur_n = 0;

    int next_l = l;
    while (!idx[cur_n].empty()) {
      if (idx[cur_n].front() < l) {
        idx[cur_n].pop();
      } else {
        next_l = max(next_l, idx[cur_n].front());
        idx[cur_n].pop();
        ++cur_n;
      }
    }

    result.push_back(cur_n);
    l = next_l + 1;
  }

  printf("%d\n", result.size());
  for (auto el: result) {
    printf("%d ", el);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    solve();
  }
}
