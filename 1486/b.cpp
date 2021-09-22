#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long solve_dimension(vector<int>& v, int n) {
  long long cnt_min = 0;
  long long cur_min = 1000000000 * 1ll * 1000000000;

  long long sum = 0;
  sort(v.begin(), v.end());

  for (auto el: v) {
    // cout << el << " ";
    sum += el;
  }
  // cout << endl;

  sum -= v[0] * 1ll * n;

  // cout << "sum: " << sum << endl;

  long long prev = v[0];
  for (int i = 0; i < n; ++i) {
    long long diff = v[i] - prev;
    int i_start = i;

    sum += diff * i;
    sum -= diff * (n - i);
    while (i + 1 < n && v[i + 1] == v[i]) {
      ++i;
    }

    prev = v[i];
    if (sum < cur_min) {
      cur_min = sum;
      cnt_min = 0;
    }

    if (sum == cur_min) {
      // cout << "cur_min: " << sum << ",i: " << i << ", diff: "<< diff << endl;
      if (n % 2 == 0 && i_start == n / 2) {
        cnt_min += max(1ll, diff);
      } else {
        cnt_min++;
      }
    }
  }

  // cout << "cnt_min " << cnt_min << endl;
  return cnt_min;
}

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }

  long long a = solve_dimension(x, n);
  long long b = solve_dimension(y, n);

  printf("%lld\n", a * b);
  // cout << cur_min << endl;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
