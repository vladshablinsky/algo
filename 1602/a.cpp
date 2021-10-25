#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
  string s;
  cin >> s;
  char min_c = s[0];
  int idx = 0;

  for (int i = 0; i < s.length(); ++i) {
    if (s[i] < min_c) {
      min_c = s[i];
      idx = i;
    }
  }

  cout << min_c << " ";
  for (int i = 0; i < s.length(); ++i) {
    if (i != idx) {
      cout << s[i];
    }
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
