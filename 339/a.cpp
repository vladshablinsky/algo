#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int main() {
  long long l, r, k;
  double eps = 1e-9;
  bool flag = false;
  cin >> l >> r >> k;

  double cur = 1;
  double counter = 0;
  while ((cur - eps) <= (double)r) {
    if (cur + eps >= (double)l) {
      flag = true;
      cout << (long long)cur << " ";
    }
    cur *= (double)k;
  }
  if (!flag) {
    cout << -1;
  }
  cout << "\n";

  return 0;
}
