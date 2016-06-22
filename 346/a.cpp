#include <iostream>
#include <cstdio>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  int cnt = mabs(b) % n;
  int k = 1;
  if (b < 0) {
    k = -1;
  }
  cout << (a - 1 + cnt * k + n) % n + 1 << "\n";

  return 0;
}
