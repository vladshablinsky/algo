#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  string s;
  cin >> s;

  if (s.front() != s.back()) {
    s[0] = s.back();
  }
  cout << s << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
