#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 200005;
int h[MAXN];

bool solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &h[i]);
  }

  // start with min, remember how much we can go up
  int up_steps = 0;
  int prev_height = h[0];
  for (int i = 1; i < n; ++i) {
    if (h[i] >= prev_height) {
      if (prev_height + k - 1 + up_steps < h[i]) {
        return false;
      }

      if (prev_height + k - 1 < h[i]) {
        up_steps -= h[i] - (prev_height + k - 1);
      } else {
        up_steps += prev_height + k - 1 - h[i];
      }

      prev_height = h[i];
    } else {
      // can't reach
      if (h[i] + k - 1 < prev_height - k + 1) {
        return false;
      }

      prev_height = max(h[i], prev_height - k + 1);
      up_steps = k - 1 - (prev_height - h[i]);
    }
  }
  return prev_height == h[n - 1];
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

