#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
  int n, s;
  cin >> n >> s;
  if (s < n) {
    cout << 1 << endl;
  } else {
    cout << s / n + !(s % n == 0) << endl;
  }
  return 0;
}
