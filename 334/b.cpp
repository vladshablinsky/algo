#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 2e5 + 10;
const int INF = 2e9;
int s[MAX_N];
int n, k;

bool can_pack(int t) {
  int l = 0;
  int r = n - 1;
  int boxes_used = 0;
  while (l <= r) {
    if (l == r) {
      if (s[l] <= t) {
        ++boxes_used;
      } else {
        return false;
      }
      break;
    } else {
      if (s[l] + s[r] <= t) {
        ++boxes_used;
        ++l;
        --r;
      } else if (s[r] <= t) {
        ++boxes_used;
        --r;
      } else {
        return false;
      }
    }
  }
  return boxes_used <= k;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &s[i]);
  }

  int ans = 2e9;
  int l = 1, r = 2e9;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (can_pack(m)) {
      ans = min(ans, m);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << ans << "\n";
  return 0;
}
