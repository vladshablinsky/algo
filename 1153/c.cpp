#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 300005;

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;

  if (n & 1) {
    cout << ":(\n";
    return 0;
  }

  int cnt_open_left = n / 2;
  for (auto c: s) {
    cnt_open_left -= (c == '(');
  }

  if (cnt_open_left < 0) {
    cout << ":(\n";
    return 0;
  }

  int cur_bal = 0;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '?') {
      if (cnt_open_left) {
        --cnt_open_left;
        s[i] = '(';
      } else {
        s[i] = ')';
      }
    }
    cur_bal += s[i] == '(';
    cur_bal -= s[i] == ')';
    if (cur_bal <= 0 && i < n - 1) {
      cout << ":(\n";
      return 0;
    }
  }

  if (cur_bal != 0) {
    cout << ":(\n";
  } else {
    cout << s << "\n";
  }
  return 0;
}
