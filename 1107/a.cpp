#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

void solve(string &s) {
  if (s[0] >= s[1] && s.length() == 2) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    cout << "2\n";
    cout << s[0] << " " << s.substr(1, s.length() - 1) << "\n";
  }
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int l;
    string s;
    cin >> l;
    cin >> s;
    solve(s);
  }
  return 0;
}
