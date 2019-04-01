#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

int main() {
  string s;
  cin >> s;
  int lu = 0;
  int rd = 0;
  for (auto c: s) {
    if (c == '0') {
      if (lu) {
        cout << "3 1\n";
      } else {
        cout << "1 1\n";
      }
      lu++;
      lu %= 2;
    } else {
      if (rd) {
        cout << "4 1\n";
      } else {
        cout << "4 3\n";
      }
      rd++;
      rd %= 2;
    }
  }
  return 0;
}
