#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int items[MAXN];

bool check(int cnt, int n, int m, int k) {
  int boxes_left = m;
  int cur_box_capacity = k;
  int cur_item = n - cnt;
  while (cur_item != n) {
    if (!boxes_left) {
      return false;
    }
    if (items[cur_item] > cur_box_capacity) {
      --boxes_left;
      cur_box_capacity = k;
    } else {
      cur_box_capacity -= items[cur_item];
      ++cur_item;
    }
  }
  return true;
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &items[i]);
  }

  int l = 0;
  int r = n;
  int ans = 0;

  while (l <= r) {
    int mid = (l + r) / 2;
    if (check(mid, n, m, k)) {
      ans = max(ans, mid);
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  cout << ans << "\n";
  return 0;
}
