#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 105;
const int MAXSUM = 200005;

int a[MAXN];
bool f_prev[MAXSUM];
bool f_cur[MAXSUM];

int main() {
  int n;
  cin >> n;
  int sum = 0;
  int min_2_pow = 32;
  int idx = -1;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    sum += a[i];

    int pow_2 = 0;
    int cur_a = a[i];
    while (cur_a % 2 == 0) {
      cur_a /= 2;
      ++pow_2;
    }
    if (pow_2 < min_2_pow) {
      min_2_pow = pow_2;
      idx = i;
    }
  }

  f_prev[0] = true;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= sum; ++j) {
      f_cur[j] = f_prev[j];
      if (j - a[i] >= 0 && f_prev[j - a[i]]) {
        f_cur[j] = true;
      }
    }
    swap(f_cur, f_prev);
  }

  if (sum % 2 == 0 && f_prev[sum / 2]) {
    cout << 1 << "\n" << idx + 1 << "\n";
  } else {
    cout << "0\n";
  }
  return 0;
}
