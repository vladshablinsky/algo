#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int w[6];
int m[6];

int main() {
  int ans = 0;
  int h_s, h_u;

  for (int i = 1; i <= 5; ++i) {
    cin >> m[i];
  }
  for (int i = 1; i <= 5; ++i) {
    cin >> w[i];
  }
  cin >> h_s >> h_u;

  for (int i = 1; i <= 5; ++i) {
    int x = i * 500;
    ans += max(75 * x, (250 - m[i]) * x - 12500 * w[i]);
  }
  ans /= 250;
  ans += (100 * h_s - 50 * h_u);
  cout << ans << "\n";
  return 0;
}
