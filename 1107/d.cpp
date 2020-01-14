#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 5200;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int a[MAXN][MAXN];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); ++j) {
      int cur_four = 0;
      if (s[j] >= '0' && s[j] <= '9') {
        cur_four = s[j] - '0';
      } else {
        cur_four = 10 + s[j] - 'A';
      }
      for (int k = 0; k < 4; ++k) {
        if (cur_four & (1 << k)) {
          a[i][(j + 1) * 4 - k - 1] = 1;
        }
      }
    }
  }

  int ans = -1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n;) {
      int cur_cnt = 1;
      while (j + cur_cnt < n && a[i][j + cur_cnt] == a[i][j]) {
        ++cur_cnt;
      }
      if (ans == -1) {
        ans = cur_cnt;
      } else {
        ans = gcd(ans, cur_cnt);
      }
      j += cur_cnt;
    }
    if (ans == 1) {
      break;
    }
  }

  if (ans != 1) {
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < n;) {
        int cur_cnt = 1;
        while (i + cur_cnt < n && a[i + cur_cnt][j] == a[i][j]) {
          ++cur_cnt;
        }
        ans = gcd(ans, cur_cnt);
        i += cur_cnt;
      }
      if (ans == 1) {
        break;
      }
    }
  }

  cout << ans << "\n";
  return 0;
}
