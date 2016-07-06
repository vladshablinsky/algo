#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

long long cb(long long x) {
  return x * x * x;
}

long long cnt(long long n) {
  long long rt = (long long)cbrt(n);
  long long ans_cnt = 0;
  for (long long i = 2; i <= rt; ++i) {
    ans_cnt += (n / cb(i));
  }
  return ans_cnt;
}

int main() {
  long long m;
  cin >> m;

  long long l = 1;
  long long r = 1e16;

  while (l <= r) {
    long long mm = (l + r) / 2;
    long long cur_cnt = cnt(mm);
    if (cur_cnt == m) {
      long long ll = l;
      long long rr = mm;
      long long ans = mm;

      while (ll <= rr) {
        long long mmm = (ll + rr) / 2;
        cur_cnt = cnt(mmm);
        if (cur_cnt < m) {
          ll = mmm + 1;
        } else {
          ans = min(ans, mmm);
          rr = mmm - 1;
        }
      }

      cout << ans << "\n";
      return 0;
    } else if (cur_cnt <= m) {
      l = mm + 1;
    } else {
      r = mm - 1;
    }
  }
  cout << "-1\n";
  return 0;
}
