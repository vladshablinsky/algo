#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MAXN = 105;

int solve(string s) {
  int cur_cnt_happy = 0;
  int cur_cnt_blank = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '+') {
      cur_cnt_blank = cur_cnt_happy + 1;
    } else {
      cur_cnt_happy = cur_cnt_blank + 1;
    }
  }
  return cur_cnt_happy;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    printf("Case #%d: %d\n", i + 1, solve(s));
  }
  return 0;
}
