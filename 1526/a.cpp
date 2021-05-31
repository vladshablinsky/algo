#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 55;
int a[MAXN];
int b[MAXN];

void solve() {
  int n;
  cin >> n;
  int ok = false;
  for (int i = 0; i < 2 * n; ++i) {
    cin >> a[i];
  }
  while (!ok) {
    ok = true;
    for (int i = 0; i < 2 * n; ++i) {
      int prev = i - 1;
      if (prev < 0) {
        prev = 2 * n - 1;
      }
      int next = i + 1;
      if (next == 2 * n) {
        next = 0;
      }
      if ((a[prev] + a[next]) % 2 == 0 && (a[prev] + a[next]) / 2 == a[i]) {
        ok = false;
        swap(a[next], a[i]);
      }
    }
  }
  for (int i = 0; i < 2 * n; ++i) {
    cout << a[i] << " ";
  }
  cout <<"\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
