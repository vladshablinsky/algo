#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int INF = 1e9;

string invert(string s) {
  for (auto& c: s) {
    if (c == '0') {
      ++c;
    } else {
      --c;
    }
  }
  return s;
}

int solve_impl(const string& s) {

  int balance = 0;
  int ans = 0;

  vector<int> neg_balance(s.length() + 2, INF);
  for (int i = 0; i < s.length(); ++i) {
    balance += s[i] == '1';
    balance -= s[i] == '0';

    // cout << "i: " << i << ", bal = " << balance << endl;

    if (balance > 0) {
      ans = (i + 1 - balance) / 2;
    } else {
      if (int idx = neg_balance[-balance + 1]; idx < i) {
        ans = max(ans, (i - idx) / 2);
      }

      neg_balance[-balance] = min(neg_balance[-balance], i);
    }
  }

  return ans;
}

void solve() {
  string s;
  cin >> s;

  cout << max(solve_impl(s), solve_impl(invert(s))) << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
