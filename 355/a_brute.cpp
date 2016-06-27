#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 105;

int a[MAXN];
int n;

int ans() {
  int max_a = -1;
  int min_a = n + 1;
  int max_a_pos = -1;
  int min_a_pos = -1;

  for (int i = 0; i < n; ++i) {
    if (a[i] < min_a) {
      min_a = a[i];
      min_a_pos = i;
    }
    if (a[i] > max_a) {
      max_a = a[i];
      max_a_pos = i;
    }
  }

  return max(max_a_pos - min_a_pos, min_a_pos - max_a_pos);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  int res = -1;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      swap(a[i], a[j]);
      res = max(res, ans());
      swap(a[i], a[j]);
    }
  }
  cout << res << "\n";
  return 0;
}


