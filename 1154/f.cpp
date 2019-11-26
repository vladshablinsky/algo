#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int MAXK = 2005;
const int MAXN = 200005;
const int INF = 1e9;

int a[MAXN];
int pref[MAXK]; // prefix sums to buy first k cheapest
int offers[MAXK]; // offers[i] is how many free when buying i
int f[MAXK]; // f[x] min cost to buy x most cheapest items

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  sort(a, a + n);
  pref[0] = a[0];
  for (int i = 1; i < k; ++i) {
    pref[i] = pref[i - 1] + a[i];
  }

  for (int i = 0; i < m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    if (x <= k) {
      offers[x] = max(offers[x], y);
    }
  }

  for (int i = 1; i <= k; ++i) {
    f[i] = f[i - 1] + a[i - 1];
    for (int j = 1; j <= i; ++j) {  // buying last k using offer
      int remain_cost = pref[i - 1];
      if (i - 1 - (j - offers[j]) >= 0) {
        remain_cost -= pref[i - 1 - (j - offers[j])];
      }

      f[i] = min(f[i], f[i - j] + remain_cost);
    }
  }
  cout << f[k] << "\n";
  return 0;
}
