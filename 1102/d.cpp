#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int CNT_SYMBOLS = 3;

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;

  vector<int> cnt_bad_right(CNT_SYMBOLS, -n/CNT_SYMBOLS);
  vector<int> cnt_left(CNT_SYMBOLS, 0);

  for (int i = 0; i < n; ++i) {
    ++cnt_bad_right[s[i] - '0'];
  }

  for (int i = 0; i < n; ++i) {
    int cur_symbol = s[i] - '0';
    if (cnt_bad_right[cur_symbol] > 0) { // vacant position
      for (int j = 0; j < CNT_SYMBOLS; ++j) {
        if (cnt_bad_right[j] >= 0) { // j must be reduced, not expand
          continue;
        }

        if (j < cur_symbol || cnt_left[cur_symbol] == n/CNT_SYMBOLS) {
          s[i] = j + '0';
          cnt_bad_right[cur_symbol]--;
          cnt_bad_right[j]++;
          break;
        }
      }
    }
    cnt_left[s[i] - '0']++;
  }

  cout << s << "\n";
  return 0;
}
