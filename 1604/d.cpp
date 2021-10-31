#include <iostream>

using namespace std;

long long solve(long long x, long long y) {
  if (x > y) {
    return x + y;
  } else if (x == y) {
    return x;
  } else {
    return y - (y % x) / 2;
  }
}

long long solve() {
  long long x;
  long long y;
  cin >> x >> y;
  return solve(x, y);
}


int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
