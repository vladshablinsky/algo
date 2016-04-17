#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <map>

using namespace std;

const int FST = 1989;

map<string, string> mp;

void prepare() {
  for (int i = FST; i <= 100000; ++i) {
    string to_s = to_string(i);
    string s;
    for (int j = 0; j < to_s.length(); ++j) {
      s.insert(0, 1, to_s[to_s.length() - 1 - j]);
      if (mp[s] == "") {
        mp[s] = to_s;
        break;
      } else if (j == 4 && mp[s] != to_s && mp[s.insert(0, 1, '1')] == "") {
        mp[s] = to_s;
      }
    }
  }
}

void solve(string s) {
  if (s.length() <= 4) {
    cout << mp[s] << '\n';
  } else {
    bool flag_ones = true;
    for (int i = 0; i < s.length() - 5; ++i) {
      if (s[i] != '1') {
        flag_ones = false;
        break;
      }
    }
    int len = s.length();
    //string a = mp[s.substr(len - 4, 4)];
    //string b =  s.substr(len - 5, 5);
    //cout << "a is " << a << endl;
    //cout << "b is " << b << endl;

    if ((mp[s.substr(len - 4, 4)] == s.substr(len - 5, 5) && flag_ones)
        || s[0] == '0') {
      s.insert(0, 1, '1');
    }
    cout << s << '\n';
  }
}

int main() {
  prepare();
  int n;
  scanf("%d", &n);
  for (int i= 0; i < n; ++i) {
    string s;
    cin >> s;
    s.erase(0, 4);
    solve(s);
  }
  return 0;
}
