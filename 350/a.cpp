#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <deque>

using namespace std;

int main() {
  int n;
  cin >> n;
  if (n / 7 == 0) {
    cout << max(n % 7 - 5, 0) << " " << n / 7 + min(n % 7, 2) << "\n";
    return 0;
  }
  cout << 2 * (n / 7) + max(n % 7 - 5, 0) << " " << 2 * (n / 7) + min(n % 7, 2) << "\n";
  return 0;
}
