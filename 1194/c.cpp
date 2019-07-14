#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

bool solve() {
  string s, t, p;
  cin >> s;
  cin >> t;
  cin >> p;

  vector<int> cnt_s_p(30, 0);
  vector<int> cnt_t(30, 0);

  for (auto c: t) {
    cnt_t[c - 'a']++;
  }

  for (auto c: p) {
    cnt_s_p[c - 'a']++;
  }

  int pos_t = 0;
  for (int i = 0; i < s.length(); ++i) {
    cnt_s_p[s[i] - 'a']++;
    if (pos_t >= t.length()) {
      return false;
    }
    if ((pos_t = t.find(s[i], pos_t)) == -1) {
      return false;
    }
    ++pos_t;
  }

  for (int i = 0; i < 30; ++i) {
    if (cnt_s_p[i] < cnt_t[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

  return 0;
}
