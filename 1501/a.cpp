#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 105;

int a[MAXN];
int b[MAXN];
int tm[MAXN];

void solve() {
  int n;
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i], &b[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &tm[i]);
  }

  int last_departure = 0;
  for (int i = 1; i <= n; ++i) {
    int time_to_travel = a[i] - b[i - 1] + tm[i];
    last_departure += time_to_travel;

    // cout << "arrives: " << last_departure << endl;

    if (i == n) {
      break;
    }
    // Stay.
    last_departure += (b[i] - a[i] + 1) / 2;
    last_departure = max(last_departure, b[i]);
    // cout << "departs: " << last_departure << " " << b[i] << " " << endl;
  }

  cout << last_departure << endl;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
