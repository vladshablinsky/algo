#include <iostream>
#include <cstdio>


using namespace std;

const int MAXN = 100005;
int a[MAXN];

int main() {
  long long ans = 0;
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n - 1; ++i) {
    if (a[i + 1] == a[i]) {
      continue;
    } else if (a[i + 1] > a[i]) {
      ans += a[i] * 1ll * (a[i + 1] - a[i]);
    } else {
      ans += (a[i] - a[i + 1]) * 1ll * (n - a[i] + 1);
    }
  }
  ans += (n - a[n - 1] + 1) * 1ll * (a[n - 1]);
  cout << ans << "\n";
  return 0;
}
