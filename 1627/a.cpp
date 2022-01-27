#include <iostream>

using namespace std;

const int INF = 1000000000;

void solve() {
  int result = -1;
  int n, m, r, c;
  cin >> n >> m >> r >> c;
  string s;

  bool any = false;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    if (s[c - 1] == 'B' && result == -1) {
      result = 1;
    }
    bool any_black = (s.find('B') != -1);
    any |= any_black;
    if (i == r - 1 && any_black) {
      result = s[c - 1] != 'B';
    }
  }

  if (result == -1 && any) {
    result = 2;
  }
  cout << result << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
