#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int INF = 1000000005;


int solve() {
  vector<int> v;
  int n;
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }

  sort(v.begin(), v.end());

  const auto ub = upper_bound(v.begin(), v.end(), 0); // first not zero
  const auto lb = lower_bound(v.begin(), v.end(), 0);
  int cnt_zeros = ub - lb;

  if (ub == v.end()) { // no positives
    return n;
  } else {
    int min_pos = *ub;

    for (int i = 1; i < n && v[i] <= 0; ++i) {
      // bad, taking positive results in discarding negative
      if (v[i] - v[i - 1] <  min_pos) {
        return ub - v.begin();
      }
    }
    return ub - v.begin() + 1; // take em all.
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
  return 0;
}
