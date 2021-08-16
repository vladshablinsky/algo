#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool check_bal(const string &s) {
  return true;
}

bool solve(string &a, string &b) {
  a.clear();
  b.clear();
  string s;
  int len;
  cin >> len;
  cin >> s;

  int same_cnt = 0;
  for (auto c: s) {
    same_cnt += c == '1';
  }

  // No way same not balanced.
  if (same_cnt % 2) {
    return false;
  }
  same_cnt /= 2;

  int com_bal = 0; // common part of a, b balance.
  int bal_a = 0; // balance of a
  for (int i = 0; i < len; ++i) {
    if (s[i] == '0') {
      if (bal_a) {
        a.push_back(')');
        b.push_back('(');
      } else {
        a.push_back('(');
        b.push_back(')');
      }
      bal_a ^= 1;
    } else {
      if (same_cnt) {
        ++com_bal;
        --same_cnt;
        a.push_back('(');
        b.push_back('(');
      } else {
        --com_bal;
        a.push_back(')');
        b.push_back(')');
      }
    }

    // balance in b
    // works for first iteration, because first iteration MUST be
    // same. Otherwise we return here.
    if (com_bal - bal_a < 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string s1, s2;
    if (solve(s1, s2)) {
      cout << "YES\n";
      cout << s1 << "\n";
      cout << s2 << "\n";
    } else {
      cout << "NO\n";
    }
  }
}
