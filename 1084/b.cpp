#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
  int n;
  long long s;
  long long sum = 0;
  vector<int> v;
  cin >> n >> s;
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
    sum += v[i];
  }

  int mn = *min_element(v.begin(), v.end());

  if (sum < s) {
    cout << -1 << "\n";
  } else {
    if (sum - mn * 1ll * n >= s) {
      cout << mn << "\n";
    } else {
      s -= (sum - mn * 1ll * n);
      cout << mn - (s + n - 1) / n << "\n";
    }
  }
  return 0;
}
