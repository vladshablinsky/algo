#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXK = 2005;
const int ROWS = 2;

int prev_f[MAXK][1 << ROWS];
int f[MAXK][1 << ROWS];

int comps_added(int from_mask, int to_mask) {
  if (from_mask == to_mask ||
      (to_mask == 0 && from_mask != 3) ||
      (to_mask == 3 && from_mask != 0)) {
    return 0;
  }

  if (min(from_mask, to_mask) == 1 && max(from_mask, to_mask) == 2) {
    return 2;
  }

  return 1;
}

int main() {
  int n;
  int k;
  cin >> n >> k;

  prev_f[1][0] = 1; // (0, 0)
  prev_f[2][1] = 1; // (0, 1)
  prev_f[2][2] = 1; // (1, 0)
  prev_f[1][3] = 1; // (1, 1)

  for (int i = 1; i < n; ++i) {
    // wipe prev layer's data.
    for (int j = 1; j <= k; ++j) {
      for (int mask = 0; mask < (1 << ROWS); ++mask) {
        f[j][mask] = 0;
      }
    }

    for (int j = 1; j <= k; ++j) {
      for (int mask = 0; mask < (1 << ROWS); ++mask) {
        if (!prev_f[j][mask]) {
          continue;
        }

        for (int to_mask = 0; to_mask < (1 << ROWS); ++to_mask) {
          int comps_to_add = comps_added(mask, to_mask);
          if (j + comps_to_add <= k) {
            f[j + comps_to_add][to_mask] += prev_f[j][mask];
            f[j + comps_to_add][to_mask] %= MOD;
          }
        }
      }
    }
    //cout << "I: " << i << endl;
    //for (int j = 1; j <= k; ++j) {
    //  cout << "comps: " << j << " -- ";
    //  for (int mask = 0; mask < (1 << ROWS); ++mask) {
    //    cout << "( " << mask << ", " << f[j][mask] << " ), ";
    //  }
    //  cout << endl;
    //}
    //int x;
    //cin >> x;

    swap(prev_f, f);
  }

  int ans = 0;
  for (int mask = 0; mask < (1 << ROWS); ++mask) {
    ans += prev_f[k][mask];
    ans %= MOD;
  }
  cout << ans << "\n";
  return 0;
}
