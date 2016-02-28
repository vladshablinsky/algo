#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> bs;
vector<int> bx;

long long f[60][2];

int main() {
  long long s, x;
  cin >> s >> x;
  if (x == 0) {
    if (s % 2 == 0) {
      cout << 1 << endl;
    } else {
      cout << 0 << endl;
    }
    return 0;
  }

  do {
    bs.push_back(s % 2);
  s /= 2;
  } while (s != 0);

  do {
    bx.push_back(x % 2);
    x /= 2;
  } while (x != 0);

  //reverse(bs.begin(), bs.end());
  //reverse(bx.begin(), bx.end());

  for (int i = 0; i < bs.size(); ++i) {
    cout << bs[i];
  }
  cout << endl;
  for (int i = 0; i < bx.size(); ++i) {
    cout << bx[i];
  }
  cout << endl;

  f[0][0] = 1;

  for (int i = 1; i <= bs.size(); ++i) {
    int cur_bit_s = (i <= bs.size() ? bs[i - 1] : 0);
    int cur_bit_x = (i <= bx.size() ? bx[i - 1]: 0);

    // 00 or 11
    if (cur_bit_x == 0 && cur_bit_s == 0) {
      // 11
      f[i][1] = f[i - 1][0];
      // 00
      f[i][0] = f[i - 1][0];
    }
    // 01 or 10
    if (cur_bit_x == 1 && cur_bit_s == 1) {
      f[i][1] = 0;
      f[i][0] = f[i - 1][0] * 2;
    }
    // 00 or 11
    if (cur_bit_x == 0 && cur_bit_s == 1) {
      f[i][0] = f[i - 1][1];
      f[i][1] = f[i - 1][1];
    }
    // 10 or 01
    if (cur_bit_x == 1 && cur_bit_s == 0) {
      f[i][1] = f[i - 1][1] * 2;
      f[i][0] = 0;
    }
  }

  if (bs.size() > bx.size()) {
    cout << f[bs.size() - 1][1] << endl;
  } else {
    if (x == s) {
      cout << max(f[bx.size()][0] - 2, 0ll) << endl;
    } else {
      cout << f[bx.size()][0] << endl;
    }
  }
  return 0;
}
