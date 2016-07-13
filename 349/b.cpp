#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

const int MAX_N = 1e5;
int a[MAX_N];

int main() {
  int n;
  long long sum = 0;
  int mx = 0;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    mx = max(mx, a[i]);
    sum += a[i];
  }

  cout << 2 * 1ll * mx - sum + 1 << "\n";

  return 0;
}
