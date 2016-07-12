#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <deque>

using namespace std;

const int MAX_N = 1e5 + 5;

int a[MAX_N];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; k - i >= 1; ++i) {
    k -= i;
  }

  cout << a[k - 1] << "\n";
  return 0;
}
