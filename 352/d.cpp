#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

const int MAX_N = 5e5 + 5;

unsigned int a[MAX_N];
long long pref[MAX_N];
int n, k;

void calc_pref() {
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + a[i];
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  sort(a + 1, a + n + 1);
  calc_pref();

  if (k == 0) {
    cout << a[n] - a[1] << "\n";
    return 0;
  }

  int l = 1, r = n;
  int idx_r_leq = 1;

  while (l <= r) {
    int m = (l + r) / 2;
    long long to_reassign_to = a[m] * 1ll * (m - 1) - pref[m - 1];
    if (to_reassign_to <= k) {
      idx_r_leq = max(idx_r_leq, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  //cout << "INDEX TO ADD TILL IS " << idx_r_leq << endl;

  long long to_add = k * 1ll - (a[idx_r_leq] * 1ll * (idx_r_leq - 1) - pref[idx_r_leq - 1]);
  long long add_to_one = to_add / (idx_r_leq);
  int cnt_to_add_extra_one = to_add % idx_r_leq;

  //cout << " TO ADD IS " << to_add << endl;
  //cout << " ADD TO ONE " << add_to_one << endl;
  //cout << " CNT TO ADD EXTRA " << cnt_to_add_extra_one << endl;

  for (int i = 1; i <= idx_r_leq; ++i) {
    a[i] = a[idx_r_leq] + (unsigned int)add_to_one;
  }
  for (int i = 0; i < cnt_to_add_extra_one; ++i) {
    ++a[idx_r_leq - i];
  }

  calc_pref();

  //for (int i = 1; i <= n; ++i) {
    //cout << a[i] << " ";
  //}
  //cout << endl;

  l = 1, r = n;
  int idx_l_geq = 0;
  while (l <= r) {
    int m = (l + r) / 2;
    long long to_reassign_from = pref[n] - pref[m] - a[m] * 1ll * (n - m);
    if (to_reassign_from >= k) {
      idx_l_geq = max(idx_l_geq, m);
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  //cout << "====================================\n";
  //cout << "INDEX TO SUBSTRACT FROM IS " << idx_l_geq << endl;

  long long extra_left = pref[n] - pref[idx_l_geq] - a[idx_l_geq] * 1ll * (n - idx_l_geq) - k;
  add_to_one = extra_left / (n - idx_l_geq);
  cnt_to_add_extra_one = extra_left % (n - idx_l_geq);

  //cout << " TO ADD IS " << extra_left << endl;
  //cout << " ADD TO ONE " << add_to_one << endl;
  //cout << " CNT TO ADD EXTRA " << cnt_to_add_extra_one << endl;

  for (int i = idx_l_geq + 1; i <= n; ++i) {
    a[i] = a[idx_l_geq] + (unsigned int)add_to_one;
  }
  for (int i = 0; i < cnt_to_add_extra_one; ++i) {
    a[n - i]++;
  }

  //for (int i = 1; i <= n; ++i) {
    //cout << a[i] << " ";
  //}
  //cout << endl;

  cout << a[n] - a[1] << endl;

  return 0;
}
