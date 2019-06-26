#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9;

void solve() {
  int n, k;
  vector<int> v;

  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int a;
    scanf("%d", &a);
    v.push_back(a);
  }

  int res = INF;
  int x = v[0];
  for (int i = k; i < n; ++i) {
    if ((v[i] - v[i - k] + 1) / 2 < res) {
      res = (v[i] - v[i - k] + 1) / 2;
      x = v[i - k] + res;
    }
  }
  printf("%d\n", x);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
