#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <map>

using namespace std;

const int FST = 1989;

map<string, string> mp;
long long sum[11];

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

void init_sum() {
  sum[1] = FST;
  long long k = 10;
  for (int i = 2; i < 11; ++i) {
    sum[i] = sum[i - 1] + k;
    k *= 10;
  }
}

void solve(string s) {
  if (s.length() <= 4) {
    cout << mp[s] << "\n";
  } else {
    string from = to_string(sum[s.length()]);
    bool less = false;
    for (int i = 0; i < s.length(); ++i) {
      if (s[i] == from[i]) {
        continue;
      } else if (s[i] > from[i]) {
        break;
      } else if (s[i] < from[i]) {
        less = true;
        break;
      }
    }
    if (less) {
      s.insert(0, 1, '1');
    }
    cout << s << "\n";
  }
}

int main() {
  init_sum();
  prepare();
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    s.erase(0, 4);
    solve(s);
  }
  return 0;
}
