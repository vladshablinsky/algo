#include <iostream>

using namespace std;

const int MAXN = 50;

int a[MAXN];

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void solve() {
  int n;
  scanf("%d", &n);
  long long sum = 0;
  long long other_sum = 0;

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
    if (i % 2 == 0) {
      other_sum += mabs(1 - a[i]);
    }
  }

  int parity = other_sum * 2 > sum; // if false, use same again
  for (int i = 0; i < n; ++i) {
    if (i % 2 == parity) {
      printf("1 ");
    } else {
      printf("%d ", a[i]);
    }
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
