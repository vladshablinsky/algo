#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
const int INF = 1000000000;

void solve() {
  int n;
  scanf("%d", &n);

  int el;
  long long ans = INF * 1ll * INF;
  long long pref = 0;
  int min_odd = INF;
  int min_even = INF;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &el);
    pref += el;
    if (i % 2) {
      min_odd = min(min_odd, el);
    } else {
      min_even = min(min_even, el);
    }

    if (i == 1) {
      continue;
    }

    long long curans = pref - min_odd - min_even;

    // thus n1 <= n2 always.
    long long n1 = n - ((i - 2) + 1) / 2; // odd
    long long n2 = n - (i - 2) / 2; // even

    curans += n1 * min_odd;
    curans += n2 * min_even;
    ans = min(ans, curans);
  }

  cout << ans << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
