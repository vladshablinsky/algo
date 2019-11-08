#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  if (k * 1ll * (k + 1) / 2 > n) {
    cout << "NO\n";
    return 0;
  }


  vector<int> v(k);
  n -= (k * (k + 1) / 2);

  int cur_to_add = k;
  int cnt = n / k;
  n %= cur_to_add;
  v[0] = 1 + cnt;

  for (int i = 1; i < k; ++i) {
    v[i] = v[i - 1] + 1;

    cur_to_add = k - i;
    cnt = min(v[i - 1] - 1, n / cur_to_add);
    n -= cur_to_add * cnt;
    v[i] += cnt;
  }

  if (n != 0) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    for (auto &el: v) {
      cout << el << " ";
    }
    cout << "\n";
  }
  return 0;
}
