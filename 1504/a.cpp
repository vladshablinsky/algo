#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
  string s;
  cin >> s;
  int len = s.length();
  bool found = false;
  for (int i = 0; i <= len / 2; ++i) {
    if (s[i] != 'a') {
      s.insert(len - i, "a");
      found = true;
      break;
    }
    if (s[len - i - 1] != 'a') {
      s.insert(i, "a");
      found = true;
      break;
    }
  }
  if (found) {
    cout << "YES\n";
    cout << s << "\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
