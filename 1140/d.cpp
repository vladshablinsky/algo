#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 2; i + 1 <= n; ++i) {
    ans += i * (i + 1);
  }
  cout << ans << "\n";
  return 0;
}
