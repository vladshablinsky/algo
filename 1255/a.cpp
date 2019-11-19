#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    int a, b;
    cin >> a >> b;
    if (a > b) {
      swap(a, b);
    }
    int d = b - a;

    int ans = 0;
    ans += d / 5;
    d = d % 5;
    ans += d / 2;
    d = d % 2;
    ans += d;
    cout << ans << "\n";
  }

  return 0;
}
