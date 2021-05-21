#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;


int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  long long r, b, d;
  cin >> r >> b >> d;

  if (r > b) {
    swap(r, b);
  }

  if (b - r - r * d > 0) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
