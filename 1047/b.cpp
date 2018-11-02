#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int xx, yy;
    cin >> xx >> yy;
    ans = max(ans, xx + yy);
  }
  cout << ans << "\n";
  return 0;
}
