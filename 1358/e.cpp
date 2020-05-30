#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 250005;
const long long INF = 1000000000 * 1ll * 1000000000;
int a[MAXN];
int a_repeated;



int main() {
  int n;
  scanf("%d", &n);
  int k = n;
  long long sum = 0;
  for (int i = 0; i < (n + 1) / 2; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }

  scanf("%d", &a_repeated);
  sum += (n / 2) * 1ll * a_repeated;

  int half = (n + 1) / 2;
  long long min_sum = 0;
  long long cur_sum = 0;
  if (sum <= 0) {
    for (int i = 0; i < (n - 1) / 2; ++i) {
      --k;
      sum -= a_repeated;
      cur_sum += (a_repeated - a[i]);
      min_sum = min(min_sum, cur_sum);
      if (sum + min_sum > 0) {
        break;
      }
    }
  }

  if (sum + min_sum <= 0) {
    k = -1;
  }
  cout << k << "\n";
  return 0;
}
