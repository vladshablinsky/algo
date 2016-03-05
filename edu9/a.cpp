#include <iostream>
#include <cstdio>

using namespace std;

int q[1005];

int main() {
  int n, p;
  scanf("%d%d", &n, &p);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s == "half") {
      q[i] = 0;
    } else {
      q[i] = 1;
    }
  }

  long long cur_cnt = 1;
  long long ans = p / 2;
  for (int i = n - 2; i >= 0; --i) {
    // was even
    if (q[i] == 1) {
      cur_cnt = cur_cnt * 2 + 1;
    } else {
      cur_cnt = cur_cnt * 2;
    }
    ans += cur_cnt * p / 2;
  }
  cout << ans << "\n";
}
