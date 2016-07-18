#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 105;

int a[MAX_N];
vector<int> v;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] == 1) {
      v.push_back(i);
    }
  }

  if (v.empty()) {
    cout << 0 << "\n";
    return 0;
  }

  if (v.size() < 2) {
    cout << 1 << "\n";
    return 0;
  }

  long long ans = 1;
  for (int i = 0; i + 1 < v.size(); ++i) {
    ans *= (v[i + 1] - v[i]);
  }
  cout << ans << "\n";
  return 0;
}

