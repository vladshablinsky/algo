#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int n, x;
    cin >> n >> x;
    cout << x * 2 << "\n";
  }
  return 0;
}
