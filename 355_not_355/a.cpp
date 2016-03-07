#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int ans = 0;
  while ((a >= 1 && b > 1) || (b >= 1 && a > 1)) {
    if (a < b) {
      a++;
      b -= 2;
    } else {
      b++;
      a -= 2;
    }
    ++ans;
  }

  cout << ans << "\n";
  return 0;
}
