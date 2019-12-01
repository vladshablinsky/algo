#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

int a[MAXN];
bool used[MAXN];


int main() {
  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  int ans = 1;
  for (int i = 0; i < n; ++i) {
    if (a[i] == -1 && !used[i]) {
      int sz = 1;
      int r = i + 2;
      int l = i - 2;
      while (r < n && a[r] == -1) {
        ++sz;
        used[r] = true;
        r += 2;
      }

      while (l >= 0 && a[l] == -1) {
        ++sz;
        used[l] = true;
        l -= 2;
      }

      if (l < 0 && r >= n) {
        //cout << "l and r out of bounds\n";
        ans = (ans * 1ll * k) % MOD;
        for (int j = 0; j < sz - 1; ++j) {
          ans = (ans * 1ll * (k - 1)) % MOD;
        }
      } else if (l < 0 || r >= n) {
        //cout << "l or r out of bounds\n";
        for (int j = 0; j < sz; ++j) {
          ans = (ans * 1ll * (k - 1)) % MOD;
        }
      } else {
        //cout << "l and r between numbers\n";
        long long f_y = (a[l] == a[r] ? 0 : 1);
        long long f_not_y = (a[l] == a[r] ? k - 1: k - 2);
        for (int j = 0; j < sz - 1; ++j) {
          long long new_f_y = f_not_y;
          long long new_f_not_y = f_not_y * (k - 2) + f_y * (k - 1);
          f_y = new_f_y % MOD;
          f_not_y = new_f_not_y % MOD;
        }
        ans = (ans * 1ll * f_not_y) % MOD;
      }
    } else if (a[i] != -1 && i >= 2 && a[i - 2] == a[i]) {
      cout << "0\n";
      return 0;
    }
  }
  cout << ans << "\n";
  return 0;
}
