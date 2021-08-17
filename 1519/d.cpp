#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5005;;
long long a[MAXN];
long long b[MAXN];

long long mul_sum_pref[MAXN];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }

  for (int i = 1; i <= n; ++i) {
    mul_sum_pref[i] = mul_sum_pref[i - 1] + a[i] * 1ll * b[i];
  }
  auto seg_mul_sum = [](int l, int r) {
    return mul_sum_pref[r] - mul_sum_pref[l - 1];
  };

  //cout << "base: " << mul_sum_pref[n] << endl;
  long long max_gain = 0;
  // begin processing centers;
  // i in this loop means middle is
  // 1) on the element i for odd-length segs
  // 2) BETWEEN i - 1 and i for even-length segs
  // n not processed since it does not matter.
  // more than that any 1-length seg does not matter, but we process
  // it to generalize the algorithm

  // accumulated sums are stored here
  for (int i = 2; i <= n; ++i) {
    long long odd_acc = a[i] * b[i];
    long long even_acc = 0;

    for (int radius = 1; i - radius >= 1 && i + radius - 1 <= n; ++radius) {
      if (i + radius <= n) {
        odd_acc += a[i - radius] * b[i + radius] + a[i + radius] * b[i - radius];
        max_gain = max(max_gain, -seg_mul_sum(i - radius, i + radius) + odd_acc);
      }
      even_acc += a[i - radius] * b[i + radius - 1] + a[i + radius - 1] * b[i - radius];
      max_gain = max(max_gain, -seg_mul_sum(i - radius, i + radius - 1) + even_acc);

      //cout << "mid: " << i << ", radius: " << radius << " even: " << even_acc << ", odd: " << odd_acc << endl;
    }
  }
  cout << mul_sum_pref[n] + max_gain << "\n";
}
