#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 1e6 + 5;
const long long INF = 1000000000ll * 1000000000ll;
int a[MAXN];
long long pref[MAXN];

int main() {
  int n;
  long long sum = 0;
  long long ans = INF;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
    pref[i] = sum;
  }

  if (sum == 1) {
    cout << "-1\n";
    return 0;
  }

  auto try_for_divisor = [&](long long divisor) {
    long long cur_ans = 0;
    for (int i = 0; i < n - 1; ++i) {
      long long rem = pref[i] % divisor;
      cur_ans += min(rem , -rem + divisor);
    }
    ans = min(ans, cur_ans);
  };

  bool has_good_divisors = false;
  for (long long i = 2; i * i <= sum; ++i) {
    if (!(sum % i)) {
      while (!(sum % i)) {
        sum /= i;
      }
      try_for_divisor(i);
    }
  }

  if (sum > 1) {
    try_for_divisor(sum);
  }
  cout << ans << "\n";
  return 0;
}
