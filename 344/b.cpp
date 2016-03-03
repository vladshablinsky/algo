#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 5005;

pair<int, int> a[MAXN];
pair<int, int> b[MAXN];

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < k; ++i) {
    int q_id, offset, color;
    cin >> q_id >> offset >> color;
    if (q_id == 1) {
      a[offset] = make_pair(color, i + 1);
    } else {
      b[offset] = make_pair(color, i + 1);
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int color = a[i].first;
      if (b[j].second > a[i].second) {
        color = b[j].first;
      }
      printf("%d ", color);
    }
    printf("\n");
  }
  return 0;
}
