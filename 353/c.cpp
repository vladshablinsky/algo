#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 1e5 + 5;
int a[MAX_N];
map<long long, int> cnt;

int main() {
  int n;
  scanf("%d", &n);

  long long p_sum = 0;
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    p_sum += t;
    ans = max(ans, ++cnt[p_sum]);
  }

  cout << n - ans << "\n";
  return 0;
}
