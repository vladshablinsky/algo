#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  vector<int> v(31, 0);
  int cnt = 0;
  for (int i = 0; i < 31; ++i) {
    if (n & (1 << i)) {
      ++v[i];
      ++cnt;
    }
  }

  if (k < cnt || k > n) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";
  for (int i = 31; i >= 0; --i) {
    while (i && v[i] && cnt < k) {
      --v[i];
      v[i - 1] += 2;
      ++cnt;
    }
    if (cnt == k) {
      for (int j = 0; j < v[i]; ++j) {
        cout << (1 << i) << " ";
      }
    }
  }
  return 0;
}
