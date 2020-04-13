#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int INF = 1e9;

pair<int, int> get_dx_dy(char c) {
  switch (c) {
    case 'U':
      return {0, 1};
    case 'D':
      return {0, -1};
    case 'L':
      return {-1, 0};
    case 'R':
      return {1, 0};
    default:
      return {0, 0};
  }
}

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
  pair<int, int> res(a);
  res.first += b.first;
  res.second += b.second;
  return res;
}

pair<int, int> operator-(const pair<int, int> &a, const pair<int, int> &b) {
  pair<int, int> res(a);
  res.first -= b.first;
  res.second -= b.second;
  return res;
}

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

bool check(string &s, int len, pair<int, int> target) {
  pair<int, int> cur_pos{0, 0};
  for (int i = max(len - 1, 0); i < s.length(); ++i) {
    cur_pos = cur_pos + get_dx_dy(s[i]);
  }

  int required_len;
  if (len == 0) {
    target = target - cur_pos;
    required_len = mabs(target.first) + mabs(target.second);
    return (len - required_len) >= 0 && !((len - required_len) & 1);
  }

  for (int i = 0; i + len - 1 < s.length(); ++i) {
    cur_pos = cur_pos - get_dx_dy(s[i + len - 1]);
    target = target - cur_pos;
    int required_len = mabs(target.first) + mabs(target.second);
    if (len - required_len >= 0 && !((len - required_len) & 1)) {
      return true;
    }
    target = target + cur_pos;
    cur_pos = cur_pos + get_dx_dy(s[i]);
  }
  return false;
}

int main() {
  string s;
  int n;
  int x, y;
  cin >> n;
  cin >> s;
  cin >> x >> y;

  int ans = INF;
  int l = 0;
  int r = n;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(s, m, {x, y})) {
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
