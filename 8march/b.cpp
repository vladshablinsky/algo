#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  string s;
  cin >> s;
  int pos_l = s.length();
  int pos_r = 0;
  for (int i = 0; i < s.length() - 1; ++i) {
    if (s[i] == 'A' && s[i + 1] == 'B') {
      pos_l = i;
      break;
    }
  }
  for (int i = s.length() - 1; i >= 1; --i) {
    if (s[i] == 'A' && s[i - 1] == 'B') {
      pos_r = i;
      break;
    }
  }

  if (pos_l >= 0 && pos_r < s.length() &&
      pos_r - pos_l > 2) {
    cout << "YES\n";
    return 0;
  }
  pos_l = s.length();
  pos_r = 0;

  for (int i = 0; i < s.length() - 1; ++i) {
    if (s[i] == 'B' && s[i + 1] == 'A') {
      pos_l = i;
      break;
    }
  }
  for (int i = s.length() - 1; i >= 1; --i) {
    if (s[i] == 'B' && s[i - 1] == 'A') {
      pos_r = i;
      break;
    }
  }

  if (pos_l >= 0 && pos_r < s.length() &&
      pos_r - pos_l > 2) {
    cout << "YES\n";
    return 0;
  }

  cout << "NO\n";
  return 0;
}
