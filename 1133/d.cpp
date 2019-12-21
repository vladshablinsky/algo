#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int MAXN = 200005;

int a[MAXN];
int b[MAXN];
map<pair<int, int>, int> mp;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;

}

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i];
  }

  int cnt_d_zero = 0;
  int cnt_d_any = 0;
  for (int i = 0; i < n; ++i) {
    if (b[i] == 0) {
      cnt_d_any += (a[i] == 0);
      cnt_d_zero += (a[i] != 0);
      continue;
    }

    if (a[i] == 0) {
      continue;
    }

    int numerator = -b[i];
    int denomenator = a[i];
    int gcd_ab = gcd(mabs(numerator), mabs(denomenator));
    numerator /= gcd_ab;
    denomenator /= gcd_ab;

    if (numerator < 0) {
      numerator *= -1;
      denomenator *= -1;
    }
    mp[{numerator, denomenator}]++;
  }

  int ans = 0;
  for (auto &el: mp) {
    ans = max(ans, el.second);
  }
  ans = max(ans, cnt_d_zero);
  cout << ans + cnt_d_any << "\n";
  return 0;
}
