#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;
int n, d, h;

vector<pair<int, int> > ans;

int main() {
  scanf("%d%d%d", &n, &d, &h);
  if (d - h > h) {
    printf("-1\n");
    return 0;
  }

  if (d == 1 && n > 2) {
    printf("-1\n");
    return 0;
  }

  int cur_vert = 2;
  for (int i = 0; i < h; ++i) {
    ans.push_back(make_pair(cur_vert, cur_vert - 1));
    cur_vert++;
  }

  if (d - h > 0) {
    ans.push_back(make_pair(1, cur_vert));
    cur_vert++;
  }

  for (int i = 0; i < d - h - 1; ++i) {
    ans.push_back(make_pair(cur_vert, cur_vert - 1));
    cur_vert++;
  }

  if (d == h) {
    while (cur_vert <= n) {
      ans.push_back(make_pair(2, cur_vert++));
    }
  } else {
    while (cur_vert <= n) {
      ans.push_back(make_pair(1, cur_vert++));
    }
  }


  for (int i = 0; i < ans.size(); ++i) {
    printf("%d %d\n", ans[i].first, ans[i].second);
  }

  return 0;
}
