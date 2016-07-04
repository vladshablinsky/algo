#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

string s;

void add_number(int x) {
  vector<char> v;
  while (x != 0) {
    v.push_back('0' + (x % 10));
    x /= 10;
  }
  for (int i = (int)v.size() - 1; i >= 0; --i) {
    s.push_back(v[i]);
  }
}

void prepare() {
  for (int i = 1; s.length() <= 1000; ++i) {
    add_number(i);
  }
}

int main() {
  prepare();
  int n;
  cin >> n;
  cout << s[n - 1] << "\n";

  return 0;
}
