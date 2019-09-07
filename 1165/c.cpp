#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

int main() {
  int n;
  string s;
  string res;
  cin >> n;
  cin >> s;

  int idx = 0;
  while (idx < n) {
    res.push_back(s[idx]);
    ++idx;
    while (idx < n && s[idx] == s[idx - 1]) {
      ++idx;
    }
    if (idx < n) {
      res.push_back(s[idx]);
    }
    ++idx;
  }

  if (res.length() % 2 != 0) {
    res.pop_back();
  }

  cout << n - res.length() << "\n";
  cout << res << "\n";
  return 0;
}
