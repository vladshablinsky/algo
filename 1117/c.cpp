#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 100005;
const long long INF = 1000000000 * 1ll * 1000000000;
pair<int, int> pref_dt[MAXN];

template<typename T>
T mabs(const T &t) {
  if (t < 0) {
    return -t;
  }
  return t;
}

int main() {
  int s_x, s_y;
  int f_x, f_y;
  cin >> s_x >> s_y;
  cin >> f_x >> f_y;
  f_x -= s_x;
  f_y -= s_y;

  int n;
  string s;
  cin >> n;
  cin >> s;
  int prev_x = 0;
  int prev_y = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'U') {
      prev_y++;
    } else if (s[i] == 'D') {
      prev_y--;
    } else if (s[i] == 'L') {
      prev_x--;
    } else {
      prev_x++;
    }
    pref_dt[i] = {prev_x, prev_y};
  }

  long long l = 0;
  long long r = INF;

  long long ans = INF;
  while (l <= r) {
    long long m = (l + r) / 2;

    long long cur_x = pref_dt[n - 1].first * 1ll * (m / n);
    long long cur_y = pref_dt[n - 1].second * 1ll * (m / n);

    if (m % n) {
      cur_x += pref_dt[m % n - 1].first;
      cur_y += pref_dt[m % n - 1].second;
    }

    if (mabs(f_x - cur_x) + mabs(f_y - cur_y) <= m) {
      ans = min(ans, m);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  if (ans == INF) {
    cout << "-1\n";
  } else {
    cout << ans << "\n";
  }

  return 0;
}
