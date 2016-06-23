#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

int n, m;
int nn, mm;
int cnt1 = 0;
int cnt2 = 0;

int a[10];
bool used[10];
int ans = 0;

void rec(int pos) {
  if (pos == cnt1 + cnt2) {
    int cur_s_pow = 1;
    int minutes = 0;
    int hours = 0;
    for (int i = cnt1 + cnt2 - 1; i >= cnt1; --i) {
      minutes += a[i] * cur_s_pow;
      cur_s_pow *= 7;
    }
    cur_s_pow = 1;
    for (int i = cnt1 - 1; i >= 0; --i) {
      hours += a[i] * cur_s_pow;
      cur_s_pow *= 7;
    }

    if (hours <= n && minutes <= m) {
      ++ans;
      //for (int i = 0; i < cnt1 + cnt2; ++i) {
        //cout << a[i] << " ";
      //}
      //cout << endl;
    }
    return;
  }

  for (int i = 0; i < 7; ++i) {
    if (used[i] == false) {
      used[i] = true;
      a[pos] = i;
      rec(pos + 1);
      used[i] = false;
    }
  }
}

int main() {
  cin >> n >> m;
  --n;
  --m;
  nn = n;
  mm = m;
  while (nn != 0) {
    nn /= 7;
    ++cnt1;
  }
  while (mm != 0) {
    mm /= 7;
    ++cnt2;
  }
  if (cnt1 == 0) {
    ++cnt1;
  }
  if (cnt2 == 0) {
    ++cnt2;
  }

  if (cnt1 + cnt2 > 7) {
    cout << "0\n";
    return 0;
  }

  //cout << "CNT1 & cnt2 " << cnt1 << " -- " << cnt2 << endl;

  rec(0);
  cout << ans << "\n";

  return 0;
}
