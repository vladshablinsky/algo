#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

long long mabs(long long x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

string replace_char(string s, char c) {
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '?') {
      s[i] = c;
    }
  }
  return s;
}

void solve(int id) {
  int pos_check = -1;
  string s_check, t_check;
  string s, t;
  cin >> s >> t;
  bool flag = false;
  bool first_greater = false;
  for (int i = 0; i < s.length(); ++i) {
    if (flag) {
      if (s[i] == '?') {
        if (first_greater) {
          s[i] = '0';
        } else {
          s[i] = '9';
        }
      }
      if (t[i] == '?') {
        if (first_greater) {
          t[i] = '9';
        } else {
          t[i] = '0';
        }
      }
    } else {
      if (s[i] != '?' && t[i] != '?') {
        flag = true;
        first_greater = (s[i] > t[i]);
        continue;
      } else if (s[i] == '?' && t[i] == '?') {
        if (i + 1 < s.length() - 1 &&
            mabs(s[i + 1] - t[i + 1]) >= 1 && s[i + 1] != '?' && t[i + 1] != '?') {
          pos_check = i;
          s_check = s;
          t_check = t;
        }
        s[i] = '0';
        t[i] = '0';
      } else {
        if (s[i] == '?') {
          s[i] = t[i];
        } if (t[i] == '?') {
          t[i] = s[i];
        }
      }
    }
  }

  long long cur_ans = mabs(atol(s.c_str()) - atol(t.c_str()));
  long long a = atol(s.c_str());
  long long b = atol(t.c_str());
  if (pos_check != -1) {
    s_check[pos_check] = 1;
    t_check[pos_check] = 0;
    long long aa = atol(replace_char(s_check, '0'));
    long long bb = atol(replace_char(t_check, '9'));
    long long cur = mabs(aa - bb);
    if (cur < cur_ans) {
      cur_ans = ans;
      a = aa;
      b = bb;
    } else if (cur == cur_ans) {
      if (a < aa) {
        a = aa;
        b = bb;
      } else if (aa == a) {
        b = min(b, bb);
      }
    }
    s_check[pos_check] = 0;
    t_check[pos_check] = 1;
    long long aa = atol(replace_char(s_check, '9'));
    long long bb = atol(replace_char(t_check, '0'));
    long long cur = mabs(aa - bb);
    if (cur < cur_ans) {
      cur_ans = ans;
      a = aa;
      b = bb;
    } else if (cur == cur_ans) {
      if (a < aa) {
        a = aa;
        b = bb;
      } else if (aa == a) {
        b = min(b, bb);
      }
    }
  }
  cout << "Case #" << id << ": " << s << " " << t << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
