#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 100005;

string ps[MAXN];

int main() {
  int n;
  cin >> n;
  for (int i = n - 1; i >= 0; --i) {
    cin >> ps[i];
  }

  char l_c = ps[0][0];
  int l_cnt = 0;
  char r_c = ps[0].back();
  int r_cnt = 0;

  int cur_ans = 0;
  for (int i = 0; i < ps[0].length(); ++i) {
    int j = 1;
    while (i + j < ps[0].length() && ps[0][i + j] == ps[0][i]) {
      ++j;
    }
    cur_ans = max(cur_ans, j);
    if (!l_cnt) {
      l_cnt = j;
    }
    r_cnt = j;
    i += j - 1;
  }

  //cout << l_c << " " << r_c << endl;

  bool is_same = (l_cnt == (int)ps[0].length());
  for (int i = 1; i < n; ++i) {
    const string &cur_s = ps[i];
    if (is_same) {
      int new_l_cnt = 0;
      for (int j = 0; j < cur_s.length(); ++j) {
        int k = 0;
        while (j + k < cur_s.length() && cur_s[j + k] == l_c) {
          ++k;
        }
        j += k;
        cur_ans = max(cur_ans, (l_cnt) * (k + 1) + k);
        if (j != cur_s.length()) {
          is_same = false;
        }

        if (!new_l_cnt) {
          new_l_cnt = l_cnt * (k + 1) + k;
        }
        r_cnt = l_cnt * (k + 1) + k;
      }
      l_cnt = new_l_cnt;
    } else {
      for (int j = 0; j < cur_s.length(); ++j) {
        if (cur_s[j] == l_c || cur_s[j] == r_c) {
          if (l_c == r_c) {
            cur_ans = max(cur_ans, l_cnt + r_cnt + 1);
          } else {
            cur_ans = max(cur_ans, max(l_cnt + 1, r_cnt + 1));
          }
        }
      }
    }
  }

  cout << cur_ans << "\n";
  return 0;
}
