#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int a[105];

int main() {
  int sum = 0;
  for (int i = 0; i < 5; ++i) {
    int t;
    cin >> t;
    a[t]++;
    sum += t;
  }
  int ans = sum;
  for (int i = 0; i <= 100; ++i) {
    if (a[i] - 2 >= 0) {
      ans = min(ans, sum - min(3, a[i]) * i);
    }
  }
  cout << ans << "\n";

  return 0;
}
