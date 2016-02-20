#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MOD = 1e9 + 7;
int n, m;
string s;

int f[2005][2005];

void calc_f() {
  f[0][0] = 1;
  f[1][1] = 1;
  for (int i = 2; i < 2005; ++i) {
    for (int j = 0; j < 2005; ++j) {
      if (j + 1 < 2005) {
        f[i][j] = f[i - 1][j + 1];
      }
      if (j - 1 >= 0) {
        f[i][j] = (f[i][j] + f[i - 1][j - 1]) % MOD;
      }
    }
  }
}

int main() {
  calc_f();
  int ans = 0;
  cin >> n >> m;
  cin >> s;

  int min_balance = 1000000000;
  int cur_balance = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '(') {
      cur_balance++;
    } else {
      cur_balance--;
    }
    min_balance = min(min_balance, cur_balance);
  }

  for (int p_len = 0; p_len <= n - m; ++p_len) {
    // cout << "p_len = " << p_len << endl;
    for (int p_bal = 0; p_bal <= p_len; ++p_bal) {
      // cout << "p_bal = " << p_bal << endl;
      int q_len = n - m - p_len;
      int p_s_bal = cur_balance + p_bal;
      if (min_balance + p_bal < 0 || p_s_bal > q_len) {
        continue;
      }


      int cur_ans = (f[p_len][p_bal] * 1ll * f[q_len][p_s_bal]) % MOD;
      ans = (ans + cur_ans) % MOD;

      //cout << "cur_ans = " << cur_ans << endl;
      //cout << "q_len = " << q_len << endl;
      //cout << "p_s_bal = " << p_s_bal << endl;
      //cout << "f[p_len][q_len] = " << f[p_len][q_len] << endl;
      //cout << "f[q_len][p_s_bal] = " << f[q_len][p_s_bal] << endl;
    }
  }

  cout << ans << endl;
  return 0;
}
