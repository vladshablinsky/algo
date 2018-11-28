#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const int MAX_N = 1e5 + 20;

int cnt_left_g[MAX_N];
int cnt_right_g[MAX_N];
int cnt_g[MAX_N];

int get_sum(int l, int r) {
  if (l > r) {
    return 0;
  }
  int res = cnt_g[r];
  if (l - 1  >= 0) {
    res -= cnt_g[l - 1];
  }
  return res;
}

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  bool has_any = false;
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'S') {
      has_any = true;
      cnt_g[i] = (i - 1>= 0 ? cnt_g[i - 1]: 0);
    } else {
      int cnt = 0;
      while (i + cnt < n && s[i + cnt] == 'G') {
        cnt_g[i + cnt] = (i + cnt - 1 >= 0 ? cnt_g[i + cnt - 1] + 1: 1);
        ++cnt;
      }
      cnt_left_g[i + cnt - 1] = cnt;
      cnt_right_g[i] = cnt;
      i += cnt - 1;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'S') {
      int left_g = (i - 1 >= 0 ? cnt_left_g[i - 1]: 0);
      int right_g = (i + 1 < n ? cnt_right_g[i + 1]: 0);
      ans = max(ans, left_g + right_g +
          (get_sum(0, i - left_g - 1) || get_sum(i + 1 + right_g, n - 1)));
    }
  }

  if (!has_any) {
    ans = n;
  }
  cout << ans << "\n";
  return 0;
}
