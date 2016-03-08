#include <iostream>
#include <string>

using namespace std;

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  for (int i = 0; i < 26; ++i) {
    bool flag = false;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == 'a' + i || s[j] == 'A' + i) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  return 0;
}
