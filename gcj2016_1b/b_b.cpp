#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<string> pos;

bool check(string s, string d) {
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] != '?' && s[i] != d[i]) {
      return false;
    }
  }
  return true;
}

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve(int id) {
  pos.clear();
  string s, t;
  cin >> s >> t;
  string cur;
  for (int i = '0'; i <= '9'; ++i) {
    cur.push_back(i);
    if (s.length() > 1) {
      for (int j = '0'; j <= '9'; ++j) {
        cur.push_back(j);
        if (s.length() > 2) {
          for (int k = '0'; k <= '9'; ++k) {
            cur.push_back(k);
            pos.push_back(cur);
            cur.pop_back();
          }
        } else {
          pos.push_back(cur);
        }
        cur.pop_back();
      }
    } else {
      pos.push_back(cur);
    }
    cur.pop_back();
  }

  //for (int i = 0; i < pos.size(); ++i) {
    //cout << pos[i] << endl;
  //}

  int ans_s = 10000000, ans_t = 10000000;
  int ans_d = 10000000;
  for (int i = 0; i < pos.size(); ++i) {
    for (int j = 0; j < pos.size(); ++j) {
      if (check(s, pos[i]) && check(t, pos[j])) {
        //cout << pos[i] << " " << pos[j] << endl;
        int a = atoi(pos[i].c_str());
        int b = atoi(pos[j].c_str());
        int cur_mabs = mabs(a - b);
        //cout << "a is " << a << endl;
        //cout << "b is " << b << endl;
        if (cur_mabs < ans_d) {
          ans_d = cur_mabs;
          ans_s = a;
          ans_t = b;
        } else if (cur_mabs == ans_d) {
          if (a < ans_s) {
            ans_s = a;
            ans_t = b;
          } else if (ans_s == a) {
            ans_t = min(ans_t, b);
          }
        }
      }
    }
  }
  printf("Case #%d: ", id);
  if (s.length() == 1) {
    printf("%d %d", ans_s, ans_t);
  } else if (s.length() == 2) {
    printf("%02d %02d", ans_s, ans_t);
  } else {
    printf("%03d %03d", ans_s, ans_t);
  }
  printf("\n");
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
