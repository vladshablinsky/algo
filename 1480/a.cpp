#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  string s;
  cin >> s;
  for (int i = 0; i < s.length(); i += 2) {
    if (s[i] == 'a') {
      s[i] = 'b';
    } else {
      s[i] = 'a';
    }
  }
  for (int i = 1; i < s.length(); i += 2) {
    if (s[i] == 'z') {
      s[i] = 'y';
    } else {
      s[i] = 'z';
    }
  }
  cout << s << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
