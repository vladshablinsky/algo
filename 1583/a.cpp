#include <iostream>
#include <cstdio>

using namespace std;

bool check(int n) {
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n;
  scanf("%d", &n);
  int sum = 0;
  int odd_idx = -1;
  int el;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &el);
    if (el % 2) {
      odd_idx = i;
    }
    sum += el;
  }

  bool prime = check(sum);
  printf("%d\n", n - prime);
  for (int i = 1; i <= n; ++i) {
    if (prime && odd_idx == i) {
      continue;
    }
    printf("%d ", i);
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
