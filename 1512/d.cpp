#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int a[MAXN];

void solve() {
  int n;
  cin >> n;
  pair<int, int> max1 = {-1, -1};
  pair<int, int> max2 = {-1, -1};
  long long sum = 0;
  n += 2;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    sum += a[i];
    if (a[i] >= max1.first) {
      swap(max1, max2);
      max1 = {a[i], i};
    } else if (a[i] >= max2.first) {
      max2 = {a[i], i};
    }
  }

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j == max1.second) {
        continue;
      }
      if (sum - a[j] - max1.first == max1.first) {
        for (int k = 0; k < n; ++k) {
          if (k == max1.second || k == j) {
            continue;
          }
          cout << a[k] << " ";
        }
        cout << "\n";
        return;
      }
    }
    swap(max1, max2);
  }
  cout << "-1\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
