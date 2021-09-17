#include <iostream>

using namespace std;

bool is_valid(const string& s) {
  int bal = 0;
  for (auto c: s) {
    bal += c == '(';
    bal -= c == ')';
    if (bal < 0) {
      return false;
    }
  }
  return bal == 0;
}

bool solve() {
  string s;
  cin >> s;
  if (s.front() == s.back()) {
    return false;
  }
  string a;
  string b;
  for (auto c: s) {
    if (c == s.front()) {
      a.push_back('(');
      b.push_back('(');
    } else if (c == s.back()) {
      a.push_back(')');
      b.push_back(')');
    } else {
      a.push_back(')');
      b.push_back('(');
    }
  }
  return is_valid(a) || is_valid(b);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
