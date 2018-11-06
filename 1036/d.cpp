#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  int n, m;
  vector<int> a, b;
  scanf("%d", &n);
  a.resize(n + 1);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &m);
  b.resize(m + 1);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &b[i]);
  }

  int idx_a = 0;
  int idx_b = 0;
  int cnt = 0;
  long long cur_s_a = a[0];
  long long cur_s_b = b[0];
  a[n] = b[m] = 0;

  while (idx_a < n && idx_b < m) {
    if (cur_s_a < cur_s_b) {
      ++cnt;
      cur_s_a += a[++idx_a];
    } else if (cur_s_a > cur_s_b) {
      cur_s_b += b[++idx_b];
    } else {
      cur_s_a = a[++idx_a];
      cur_s_b = b[++idx_b];
    }
  }
  if (idx_a != n || idx_b != m || cur_s_a != cur_s_b) {
    cout << "-1\n";
  } else {
    cout << n - cnt << "\n";
  }
  return 0;
}
