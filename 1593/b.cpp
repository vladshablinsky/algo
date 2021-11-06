#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> digits_idx[10];

int solve() {
  long long n;
  scanf("%lld", &n);

  if (n == 0) {
    return 0;
  }

  int idx = 0;
  for (int i = 0; i < 10; ++i) {
    digits_idx[i].clear();
  }

  do {
    digits_idx[n % 10].push_back(idx);
    ++idx;
    n /= 10;
  } while (n);

  int ans = 20;
  // 00
  if (digits_idx[0].size() > 2) {
    ans = digits_idx[0][1] - 1;
  }

  vector<pair<int, int>> digits {{0, 0}, {5, 0}, {7, 5}, {2, 5}};
  for (auto [f, s]: digits) {
    vector<int>::iterator it;
    if (digits_idx[s].size() &&
        (it = upper_bound(digits_idx[f].begin(), digits_idx[f].end(), digits_idx[s].front())) != digits_idx[f].end()) {
      ans = min(ans, *it - 1);
    }
  }
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}

