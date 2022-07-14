#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kMaxN = 100005;
constexpr int kMod = 1000000007;

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> idx(n, 0);
  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    idx[el] = i;
  }

  long long ans = 1;
  if (n != 1) {
    int l = idx[0];
    int r = idx[1];

    if (l > r) {
      swap(l, r);
    }

    int fixed = 2;
    // at i'th step we calculate number of ways to place all till i
    // meaning 0 ... i - 1 first already fixed and now we place i
    for (int i = 2; i < n; ++i) {
      // lies inside, thus may occupy any floating position in there
      if (idx[i] >= l && idx[i] <= r) {
        int multiplier = r - l + 1 - i;
        ans *= multiplier;
        ans %= kMod;
      } else {
        l = min(l, idx[i]);
        r = max(r, idx[i]);
      }
    }
  }
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
