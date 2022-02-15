#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  string s;
  cin >> s;

  int n = s.length();
  for (int i = n - 1; i > 0; --i) {
    if (auto c = s[i] + (s[i - 1] - '0'); c > '9') {
      s[i - 1] = '1';
      s[i] = c - 10;
      cout << s << "\n";
      return;
    }
  }
  //cout << "yo\n";

  for (int i = 0; i < n - 1; ++i) {
    if (s[i + 1] != '0') {
      s[i] += (s[i + 1] - '0');
      s.erase(s.begin() + i + 1);
      cout << s << "\n";
      return;
    }
  }
  s.pop_back();
  cout << s << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
