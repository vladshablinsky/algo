#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

string s, t;

int main() {
  cin >> s >> t;
  int ans = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s.substr(i, min((int)t.length(), (int)s.length() - i)) == t) {
      i = i + t.length() - 1;
      ++ans;
    }
  }
  cout << ans << endl;
  return 0;
}
