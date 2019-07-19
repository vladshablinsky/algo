#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;
int sieve[MAX_N];

int main() {
  int n;
  scanf("%d", &n);
  int cur = 1;
  for (int i = 2; i * i <= n; ++i) {
    if (!sieve[i]) {
      sieve[i] = cur;
      for (int j = i * i; j <= n; j += i) {
        sieve[j] = cur;
      }
      ++cur;
    }
  }

  for (int i = 2; i <= n; ++i) {
    if (!sieve[i]) {
      printf("%d ", cur++);
    } else {
      printf("%d ", sieve[i]);
    }
  }
  return 0;
}
