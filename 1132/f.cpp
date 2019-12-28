#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 501;
const int MAXP = 26;
const int EMPTY = 26;
const int INF = 1e9;

int prev_f[MAXN][MAXP]; // prev_f(i, j) is min ops to leave only symbols j for (i...i+k) substr
int cur_f[MAXN][MAXP]; // cur_f(i, j) is min ops to leave only symbols j for (i..i+k+1) substr

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);
  int n;
  string s;
  cin >> n;
  cin >> s;


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < MAXP; ++j) {
      prev_f[i][j] = INF;
    }
    int cur_c = s[i] - 'a';
    prev_f[i][cur_c] = 0;
  }

  for (int substr_len = 2; substr_len <= n; ++substr_len) {
    for (int i = 0; i + substr_len - 1 < n; ++i) {
      int first_c = s[i] - 'a';
      int last_c = s[i + substr_len - 1] - 'a';

      for (int j = 0; j < MAXP; ++j) {
        cur_f[i][j] = INF;
      }

      for (int j = 0; j < MAXP; ++j) {
        cur_f[i][j] = min(cur_f[i][j], prev_f[i][j] + (last_c != j));
        cur_f[i][j] = min(cur_f[i][j], prev_f[i + 1][j] + (first_c != j));
        cur_f[i][first_c] = min(cur_f[i][first_c], prev_f[i + 1][j] + (first_c != j));
        cur_f[i][last_c] = min(cur_f[i][last_c], prev_f[i][j] + (last_c != j));
      }

      cout << "substr: " << s.substr(i, substr_len) << endl;
      for (int j = 0; j < MAXP; ++j) {
        if (cur_f[i][j] != INF) {
          cout << "squeeze to " << char(j + 'a') << " takes " << cur_f[i][j] << endl;

        }
      }

    }
    swap(cur_f, prev_f);
  }

  //cout << "substr: " << s.substr(0, n) << endl;
  int ans = INF;
  for (int j = 0; j < MAXP; ++j) {
    if (prev_f[0][j] != INF) {
      //cout << "squeeze to " << char(j + 'a') << " takes " << prev_f[0][j] << endl;
    }
    ans = min(ans, prev_f[0][j] + 1);
  }
  cout << ans << "\n";
  return 0;
}
