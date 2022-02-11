#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  cin >> n;

  int rem = n % 7;

  int last_digit = n % 10;
  int add = 7 - rem;
  int sub = rem;

  // rem <= 6
  if (last_digit - sub >= 0) {
    n -= sub;
  } else {
    n += add;
  }

  cout << n << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
