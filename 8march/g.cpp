#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

string s;
string result;

int main() {
  getline(cin, s);
  bool prev_letter = false;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == ' ') {
      continue;
    } else if (s[i] == '.' || s[i] == '!' || s[i] == '?' || s[i] == ',') {
      result.push_back(s[i]);
      result.push_back(' ');
      prev_letter = false;
    } else {
      if (i - 1 >= 0 && s[i - 1] == ' ' && result.length() > 0
          && result[result.length() - 1] != ' ') {
        result.push_back(' ');
      }
      result.push_back(s[i]);
      prev_letter = true;
    }
  }

  //cout << "_";
  cout << result;
  //cout << "_\n";

  return 0;
}
