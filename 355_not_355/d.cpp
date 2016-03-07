#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5e5 + 5;
string s;
long long pref_time_r[MAXN];

int main() {
  int n;
  long long a, b, t;
  cin >> n >> a >> b >> t;
  cin >> s;


  if (s[0] == 'w') {
    pref_time_r[0] = b;
  }

  for (int i = 1; i < n; ++i) {
    pref_time_r[i] = pref_time_r[i - 1];
    if (s[i] == 'w') {
      pref_time_r[i] += b;
    }
  }

  //for (int i = 0; i < n; ++i) {
    //cout << pref_time_r[i] << " ";
  //}
  //cout << endl;

  int ans = 0;


  // try k photos right and others left
  for (int k = 0; k < n; ++k) {
    //cout << " k = " << k << endl;
    long long spent_time = 0;
    spent_time = pref_time_r[k] + (k + 1)  + k * a;
    if (spent_time > t) {
      break;
    }

    //cout << "Spent time is " << spent_time << endl;

    int left_items = n - k - 1;


    //cout << "left items " << left_items << endl;

    int ll = 0;
    int rr = left_items;
    while (ll <= rr) {
      int m = (ll + rr) / 2;
      //cout << "m = " << m << endl;
      long long s_time = (k + m) * a + (pref_time_r[n - 1] - pref_time_r[n - 1 - m]) + m;
      //cout << " s_time " << s_time << endl;
      if (spent_time + s_time <= t) {
        //cout << "SPENT_TIME + S_TIME" << spent_time + s_time << endl;
        ans = max(ans, k + m + 1);
        ll = m + 1;
      } else {
        rr = m - 1;
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    //cout << " k = " << k << endl;
    long long spent_time = 0;
    spent_time = pref_time_r[0] + (pref_time_r[n - 1] - pref_time_r[n - 1 - k]) +
      (k + 1) + k * a;
    if (spent_time > t) {
      break;
    }

    int left_items = n - k - 1;

    int ll = 0;
    int rr = left_items;
    while (ll <= rr) {
      int m = (ll + rr) / 2;
      long long s_time = (k + m) * a + (pref_time_r[m] - pref_time_r[0]) + m;
      //cout << " s_time " << s_time << endl;
      if (spent_time + s_time <= t) {
        //cout << "SPENT_TIME + S_TIME" << spent_time + s_time << endl;
        ans = max(ans, k + m + 1);
        ll = m + 1;
      } else {
        rr = m - 1;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}
