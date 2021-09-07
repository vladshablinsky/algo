#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;
const int INF = 1000000000;
int h[MAXN];

bool solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }

  // range where the block items can present
  std::pair<int, int> prev_range{h[0], h[0] + k - 1};
  for (int i = 1; i < n; ++i) {
    // To high or too low
    if (h[i] > prev_range.second || h[i] + k - 1 + k - 1 < prev_range.first) {
      return false;
    }
    prev_range.first = max(prev_range.first - k + 1, h[i]);
    prev_range.second = min(prev_range.second + k - 1, h[i] + k - 1 + k - 1);
  }

  return prev_range.first <= h[n - 1] && prev_range.second >= h[n - 1];
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
