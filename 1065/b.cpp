#include <iostream>

using namespace std;

int main() {
  long long n, m;
  cin >> n >> m;
  long long min_cnt_isolated = max(0ll, n - m * 2);
  long long max_cnt_isolated = 0ll;
  long long l = 0;
  long long r = n;
  while (l <= r) {
    long long md = (l + r) / 2;
    if ((md * (md - 1) / 2 >= m)) {
      max_cnt_isolated = max(max_cnt_isolated, n - md);
      r = md - 1;
    } else {
      l = md + 1;
    }
  }
  cout << min_cnt_isolated << " " << max_cnt_isolated << "\n";
  return 0;
}
