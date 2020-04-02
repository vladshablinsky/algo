#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MAXN = 1000005;

int calc(string &s, int start, int end, int iter, char open, char close) {
  int eligible_pos_cnt = 0;
  int cur_bal = 0;
  int min_bal = MAXN;
  bool can_add = true;
  for (int i = start; i != end + iter; i += iter) {
    cur_bal += (s[i] == open);
    cur_bal -= (s[i] == close);
    min_bal = min(min_bal, cur_bal);
    eligible_pos_cnt += (can_add && s[i] == close);

    if (cur_bal < 0) {
      can_add = false;
    }
  }
  return eligible_pos_cnt * (cur_bal == -2 && min_bal == -2);
}

int main() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  cout << calc(s, 0, n - 1, 1, '(', ')') + calc(s, n - 1, 0, -1, ')', '(') << "\n";
  return 0;
}
