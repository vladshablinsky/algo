#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int MAX_N = 1e5 + 5;
const int ENSURE_VAL = 105;

string s;
string ans;

int b;
int pos = -1;

int main() {
  cin >> s;
  string::size_type sz;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] != '.' && s[i] != 'e') {
      ans.push_back(s[i]);
    }
    if (s[i] == 'e') {
      b = stoi(s.substr(i + 1, s.length() - i - 1), &sz);
      break;
    }
    if (s[i] == '.') {
      pos = i;
    }
  }

  for (int i = 0; i < ENSURE_VAL; ++i) {
    ans.push_back('0');
  }

  ans.insert(pos + b, ".");

  while (ans[ans.length() - 1] == '0') {
    ans.erase(ans.begin() + ans.length() - 1);
  }
  if (ans[ans.length() - 1] == '.') {
    ans.erase(ans.begin() + ans.length() - 1);
  }


  while (ans[0] == '0' && ans.length() > 1 && ans[1] != '.') {
    ans.erase(ans.begin());
  }
  cout << ans << "\n";
  return 0;
}
