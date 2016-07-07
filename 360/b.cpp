#include <iostream>
#include <cstdio>

using namespace std;

const int MAX_N = 1e5 + 10;

string s;

int main() {
  cin >> s;
  cout << s;
  for (int i = s.length() - 1; i >= 0; --i) {
    cout << s[i];
  }
  cout << "\n";
  return 0;
}
