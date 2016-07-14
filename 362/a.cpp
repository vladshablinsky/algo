#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;

int main() {
  long long t, s;
  long long x;
  cin >> t >> s;
  cin >> x;

  if (x == t) {
    cout << "YES\n";
    return 0;
  }
  if (x == t + 1) {
    cout << "NO\n";
    return 0;
  }
  if (x - t >= 0 && ((x - t) % s) == 0) {
    cout << "YES\n";
    return 0;
  }
  if (x - t - 1 >= 0 && ((x - t- 1) % s) == 0) {
    cout << "YES\n";
    return 0;
  }
  cout << "NO\n";
  return 0;
}
