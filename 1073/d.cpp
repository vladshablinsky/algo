#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 200005;
long long a[MAXN];

int main() {
  int n;
  long long t;
  cin >> n >> t;
  long long ans = 0;
  long long sum = 0;
  long long cnt = n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    sum += a[i];
  }

  while (cnt) {
    ans += (t / sum) * cnt;
    t = t % sum;
    long long cur_sum = 0;
    for (int i = 0; i < n; ++i) {
      if (cur_sum + a[i] <= t) {
        cur_sum += a[i];
      } else {
        sum -= a[i];
        cnt -= (a[i] != 0);
        a[i] = 0;
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
