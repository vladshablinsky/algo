#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

long long solve() {
  int n;
  scanf("%d", &n);
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
  }

  long long ans = 0;
  map<int, int> cnt_before;
  for (int i = 0; i < n; ++i) {
    long long target_first = sum * 2 - n * 1ll * a[i];
    if (target_first % n) {
      continue;
    }
    target_first /= n;
    ans += cnt_before[target_first];

    cnt_before[a[i]]++;
  }

  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%lld\n", solve());
  }
}
