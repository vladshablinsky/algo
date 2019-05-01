#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool check(char a, char b) {
  if (a + 1 == b || b + 1 == a) {
    return true;
  } else {
    return false;
  }
}

string solve(string &s) {
  map<char, int> mp;

  for (auto c: s) {
    mp[c]++;
  }

  string a;
  string b;

  for (auto p: mp) {
    string cur_s;
    for (int i = 0; i < p.second; ++i) {
      cur_s.push_back(p.first);
    }
    if (a.empty() || !check(a.back(), p.first)) {
      a += cur_s;
    } else {
      b += cur_s;
    }
  }
  if (b.empty()) {
    return a;
  }

  if (!check(b.back(), *a.begin())) {
    return b + a;
  } else if (!check(*b.begin(), a.back())) {
    return a + b;
  } else {
    return "No answer";
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    cout << solve(s) << "\n";
  }

  return 0;
}
