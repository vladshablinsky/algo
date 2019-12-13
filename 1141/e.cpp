#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 200005;
long long d[MAXN];

int main() {
  long long h;
  long long min_pref = 0;
  int n;
  cin >> h >> n;

  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    cin >> d[i];
    sum += d[i];
    min_pref = min(min_pref, sum);
  }

  if (sum >= 0 && h + min_pref > 0) {
    cout << "-1\n";
  } else {
    long long ans;
    if (h + min_pref <= 0) {
      ans = 0;
    } else {
      ans = (h + min_pref - sum - 1) / -sum;
    }
    h += sum * ans;
    ans *= n;

    int cur_idx = 0;
    while (cur_idx < n && h + d[cur_idx] > 0) {
      h += d[cur_idx++];
      ++ans;
    }
    cout << ans + 1 << "\n";
  }

  return 0;
}
