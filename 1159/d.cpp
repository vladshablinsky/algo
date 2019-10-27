#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;


int main() {
  int n, m;
  cin >> n >> m;
  int period = (n - m) / 2 + 1;
  for (int i = 0; i < n; ++i) {
    if ((i + 1) % period == 0) {
      cout << "1";
    } else {
      cout << "0";
    }
  }
  cout << "\n";
  return 0;
}
