#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int MAX_N = 2e5 + 5;
const int MAX_POWER = 19;
const int INF = 1e9;

int a[MAX_N];
int b[MAX_N];
int f_max[MAX_N][MAX_POWER];
int f_min[MAX_N][MAX_POWER];
int pwr;
int n;

void init() {
  int cur_p = 2;
  for (int j = 1; j < MAX_POWER; ++j) {
    for (int i = 0; i + cur_p - 1 < n; ++i) {
      f_max[i][j] = max(f_max[i][j - 1], f_max[i + cur_p / 2][j - 1]);
      f_min[i][j] = min(f_min[i][j - 1], f_min[i + cur_p / 2][j - 1]);
    }
    cur_p *= 2;
  }
  pwr = cur_p;
}

int min_q(int l, int r) {
  int ans = INF;
  //cout << "MIN FROM " << l << " TO " << r << " IS ";
  for (int j = MAX_POWER; j >= 0 && l <= r; --j) {
    if (l + (1 << j) - 1 <= r) {
      ans = min(ans, f_min[l][j]);
      l = l + (1 << j);
    }
  }
  //cout << ans << endl;
  return ans;
}

int max_q(int l, int r) {
  //cout << "MAX FROM " << l << " TO " << r << " IS ";
  int ans = -INF;
  for (int j = MAX_POWER; j >= 0 && l <= r; --j) {
    if (l + (1 << j) - 1 <= r) {
      ans = max(ans, f_max[l][j]);
      l = l + (1 << j);
    }
  }
  //cout << ans << endl;
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    f_max[i][0] = a[i];
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
    f_min[i][0] = b[i];
  }

  init();

  long long ans = 0;

  for (int i = 0; i < n; ++i) {
    //cout << "INSPECTING STARTING FROM " << i << endl;
    int l = i;
    int r = n - 1;
    int first_equals_pos = INF;
    while (l <= r) {
      int m = (l + r) / 2;
      int min_im = min_q(i, m);
      int max_im = max_q(i, m);
      if (max_im >= min_im) {
        if (max_im == min_im) {
          first_equals_pos = min(first_equals_pos, m);
        }
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    if (first_equals_pos != INF) {
      //cout << "FIRST EQUALS POS IS " << first_equals_pos << endl;
      l = first_equals_pos;
      r = n - 1;
      int max_right_equals_pos = l;
      while (l <= r) {
        int m = (l + r) / 2;
        int min_im = min_q(i, m);
        int max_im = max_q(i, m);
        if (min_im == max_im) {
          max_right_equals_pos = max(max_right_equals_pos, m);
          l = m + 1;
        } else {
          r = m - 1;
        }
      }
      //cout << "LAST EQUALS POS IS " << max_right_equals_pos << endl;
      ans += (max_right_equals_pos - first_equals_pos + 1);
    }
  }

  cout << ans << "\n";
  return 0;
}
