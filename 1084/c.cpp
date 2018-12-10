#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>

using namespace std;

const int MOD = 1e9 + 7;

string squeeze(const string &s) {
  string res;
  bool free_b = false;
  for (char c: s) {
    if (c == 'a') {
      res.push_back(c);
      free_b = false;
    } else if (c == 'b') {
      if (!free_b && !res.empty()) {
        res.push_back(c);
        free_b = true;
      }
    }
  }
  return res;
}

int main() {
  string s;
  cin >> s;
  s = squeeze(s);

  vector<int> f(s.length(), 0); // f_i cnt of subs ending with a in i'th pos of s
  if (s.empty()) {
    cout << 0 << "\n";
  } else {
    int ans = 1;
    int cnt_a = 0;
    for (int i = 0; i < s.length(); ++i) {
      if (s[i] == 'b') {
        ans = (ans * 1ll * (cnt_a + 1)) % MOD;
        cnt_a = 0;
      } else {
        ++cnt_a;
      }
    }
    ans = (ans * 1ll * (cnt_a + 1)) % MOD;
    cout << ans - 1 << "\n";
  }
  return 0;
}
