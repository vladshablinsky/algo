#include <iostream>

using namespace std;

long long ans(long long n, long long m, long long k) {
  if (n > k || m > k) {
    return -1;
  } else {
    long long ones_x = (n + ((k - n) / 2) * 2);
    long long zeros_x = k - ones_x;
    long long ones_y = (m + ((k - m) / 2) * 2);
    long long zeros_y = k - ones_y;

    return min(ones_x, ones_y) - (zeros_x && zeros_y);
  }
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    long long a, b, c;
    cin >> a >> b >> c;
    cout << ans(a, b, c) << "\n";
  }
  return 0;
}
