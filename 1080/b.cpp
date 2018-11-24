#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;

long long solve(long long r) {
  long long x = (r / 2) * (r / 2 + 1);
  long long y = (((r + 1) / 2) * ((r + 1) / 2 + 1) - (r + 1) / 2);
  return -y + x;
}

int main() {
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    cout << solve(r) - solve(l - 1) << "\n";
  }
  return 0;
}
