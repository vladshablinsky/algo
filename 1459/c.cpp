#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<long long> a(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  sort(a.begin(), a.end(), std::greater<long long>());
  long long g = a.front() - a.back();
  for (int i = 0; i < n - 1; ++i) {
    g = gcd(g, a[i] - a.back());
  }
  long long cur_b;
  for (int i = 0; i < m; ++i) {
    scanf("%lld", &cur_b);
    printf("%lld ", gcd(g, a.back() + cur_b));
  }
  printf("\n");
}
