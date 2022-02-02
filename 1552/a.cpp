#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  string t = s;
  sort(t.begin(), t.end());
  int result = 0;
  for (int i = 0; i < n; ++i) {
    result += t[i] != s[i];
  }

  printf("%d\n", result);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}

