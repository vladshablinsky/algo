#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5e5 + 5;

int a[MAXN];
long long pref[MAXN];
long long alices_force_pref[MAXN];
string s;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    pref[i] = pref[i - 1] + a[i];
  }
  cin >> s;

  for (int i = 1; i <= n; ++i) {
    alices_force_pref[i] = alices_force_pref[i - 1];
    if (s[i - 1] == 'A') {
      alices_force_pref[i] += a[i];
    }
  }

  long long ans = 0;

  // prefix
  for (int i = 0; i <= n; ++i) {
    long long alices_force = alices_force_pref[n] - alices_force_pref[i] +
      pref[i] - alices_force_pref[i];
    long long bobs_force = pref[n] - alices_force;
    ans = max(ans, bobs_force);
  }

  // suffix
  for (int i = 1; i <= n; ++i) {
    long long alices_force = alices_force_pref[i - 1] + (pref[n] - pref[i - 1] -
        (alices_force_pref[n] - alices_force_pref[i - 1]));
    long long bobs_force = pref[n] - alices_force;
    ans = max(ans, bobs_force);
  }

  cout << ans << "\n";

  return 0;
}
