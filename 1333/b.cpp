#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

int a[MAXN];
int b[MAXN];

void solve() {
  int cnt_neg_one = 0;
  int cnt_one = 0;
  int n;
  scanf("%d", &n);

  int cur;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    cnt_neg_one += (a[i] == -1);
    cnt_one += (a[i] == 1);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &b[i]);
  }
  for (int i = n - 1; i >= 0; --i) {
    cnt_neg_one -= (a[i] == -1);
    cnt_one -= (a[i] == 1);
    if ((b[i] > a[i] && !cnt_one) || (b[i] < a[i] && !cnt_neg_one)) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
