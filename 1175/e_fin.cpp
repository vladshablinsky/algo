#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;
const int MAX_N = 5e5 + 5;
const int MAX_P = 21;

int f[MAX_N][MAX_P];
int next_right[MAX_N];
int n, m;

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    next_right[l] = max(next_right[l], r);
  }

  for (int i = 1; i < MAX_N; ++i) {
    next_right[i] = max(next_right[i], i);
    next_right[i] = max(next_right[i], next_right[i - 1]);
    f[i][0] = next_right[i];
  }

  f[0][0] = next_right[0];
  for (int j = 1; j < MAX_P; ++j) {
    for (int i = 0; i < MAX_N; ++i) {
      f[i][j] = f[f[i][j - 1]][j - 1];
    }
  }

  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    int cur_p = MAX_P - 1;
    // cout << "x: " << x << ", y: " << y << endl;

    int ans = 0;
    for (int j = MAX_P - 1; j >= 0; --j) {
      if (f[x][j] < y) {
        // cout << "f[" << x << "][" << j << "] = " << f[x][j] << endl;
        x = f[x][j];
        ans += 1 << j;
      }
    }
    ++ans;
    if (ans <= n) {
      cout << ans << "\n";
    } else {
      cout << "-1\n";
    }
  }
  return 0;
}
