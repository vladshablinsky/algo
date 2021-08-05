#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  string s;
  int zeros_credits, ones_credits;
  cin >> zeros_credits >> ones_credits;
  cin >> s;
  int n = s.length();
  int mid = n / 2;

  vector<pair<int, int>> free_pos;

  // central is processed separately!
  for (int i = 0; i < mid; ++i) {
    int i_rev = n - 1 - i;
    if (s[i] == '?') {
      zeros_credits -= 2 * (s[i_rev] == '0');
      ones_credits -= 2 * (s[i_rev] == '1');
      if (s[i_rev] == '?') {
        free_pos.emplace_back(i, i_rev);
      } else {
        s[i] = '0' + (s[i_rev] == '1');
      }
    } else {
      if (s[i_rev] != '?' && s[i] != s[i_rev]) {
        // no way.
        zeros_credits = -1;
        ones_credits = -1;
        break;
      }

      zeros_credits -= 2 * (s[i] == '0');
      ones_credits -= 2 * (s[i] == '1');
      s[i_rev] = '0' + (s[i] == '1');
    }
  }

  if (zeros_credits < 0 || ones_credits < 0) {
    cout << "-1\n";
    return;
  }

  if (n % 2 == 1) {
    if (s[mid] == '?') {
      s[mid] = '0' + (ones_credits % 2);
    }

    zeros_credits -= s[mid] == '0';
    ones_credits -= s[mid] == '1';
  }

  //cout << "now s: " << s << ", " << zeros_credits << ", " << ones_credits <<  endl;

  while (zeros_credits >= 2 && !free_pos.empty()) {
    s[free_pos.back().first] = s[free_pos.back().second] = '0';
    zeros_credits -= 2;
    free_pos.pop_back();
  }
  while (ones_credits >= 2 && !free_pos.empty()) {
    s[free_pos.back().first] = s[free_pos.back().second] = '1';
    ones_credits -= 2;
    free_pos.pop_back();
  }

  if (s.find('?') != std::string::npos || !!ones_credits || !!zeros_credits) {
    cout << "-1\n";
  } else {
    cout << s <<"\n";
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
