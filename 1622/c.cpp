#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 200005;
constexpr int kInf = 1000000009;
int a[kMaxN];

long long solve(int n, long long k) {
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += a[i];
  }

  long long ans = kInf * 1ll * kInf;
  if (sum <= k) {
    ans = 0;
  }

  long long steps = 0;
  long long subtr_sum = 0;
  while (n - steps - 1 > 0) {
    subtr_sum += (a[n - 1 - steps] - a[0]);
    ++steps;
    long long remain_subtr = max(0ll, (sum - subtr_sum) - k);

    ans = min(ans, steps + (remain_subtr + steps) / (steps + 1));

    // printf("subtr sum: %lld, steps: %lld, rem: %lld, ans: %lld\n", subtr_sum, steps, remain_subtr, ans);
  }

  if (!steps) {
    ans = max(0ll, (sum - subtr_sum) - k);
  }

  return ans;
}

void solve() {
  int n;
  long long k;
  scanf("%d%lld", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  sort(a, a + n);

  long long ans = solve(n, k);
  a[0]--;
  ans = min(ans, 1 + solve(n, k));
  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
