#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1000006;
const double EPS = 1e-9;

int n;
double a[MAXN];

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    a[i] = t;
  }

  double cur_val = a[n - 1];
  int cur_cnt = 1.0;
  for (int i = n - 2; i >= 0; --i) {
    if (a[i] + EPS  > cur_val / cur_cnt) {
      cur_val += a[i];
      cur_cnt++;
    } else {
      for (int j = 0; j < cur_cnt; ++j) {
        a[i + j + 1] = cur_val / cur_cnt;
      }
      cur_val = a[i];
      cur_cnt = 1.0;
    }
  }

  for (int j = 0; j < cur_cnt; ++j) {
    a[j] = cur_val / cur_cnt;
  }

  for (int i = 0; i < n; ++i) {
    printf("%.8f\n", a[i]);
  }

  return 0;
}
