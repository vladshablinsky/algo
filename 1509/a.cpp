#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 2005;
int a[MAXN];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a, a + n, [](int a, int b) { return a % 2 > b % 2; });
  for (int i = 0; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
