#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int x;
  cin >> x;
  cout << x / 5 + (x % 5 != 0) << "\n";
  return 0;
}
