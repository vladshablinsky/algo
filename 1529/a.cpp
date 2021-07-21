#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 105;
const int INF = 1000000000;
int a[105];

void solve() {
  int n;
  cin >> n;
  int mn = INF;
  int cnt_mn = 0;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    mn = min(mn, a[i]);
  }

  for (int i = 0; i < n; ++i) {
    cnt_mn += (a[i] == mn);
  }

  cout << n - cnt_mn << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
