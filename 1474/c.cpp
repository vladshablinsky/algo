#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 2005;
const int MAXVAL = 1000005;
int a[MAXN];
int cnt[MAXVAL];

void reset_cnt() {
  std::memset(cnt, 0, sizeof(cnt));
}

// index of element we use as a[0] + a[i] on the first iter
bool check(int i, int n, vector<pair<int, int>>& result) {
  // cout << "check " << a[i] << endl;
  int x = a[0]; // <-- max of two
  int y = a[i];
  result.emplace_back(x, y);
  --cnt[x];
  --cnt[y];

  for (int j = 1; j < 2 * n; ++j) {
    if (j == i || !cnt[a[j]]) {
      continue;
    }

    // cur max should add up to x with smth.
    // note the case when x = max + max
    bool same = x - a[j] == a[j];
    if (x - a[j] <= 0 || (cnt[x - a[j]] < 1 + static_cast<int>(same))) {
      break;
    }
    y = x - a[j];
    x = a[j];
    // if (x < y) {
    //   swap(x, y);
    // }
    --cnt[x];
    --cnt[y];
    result.emplace_back(x, y);
  }

  if (result.size() == n) {
    return true;
  } else {
    for (auto [f, s]: result) {
      ++cnt[f];
      ++cnt[s];
    }
    result.clear();
    return false;
  }
}

void solve() {
  reset_cnt();
  int n;
  scanf("%d", &n);
  for (int i = 0; i < 2 * n; ++i) {
    scanf("%d", &a[i]);
    ++cnt[a[i]];
  }
  sort(a, a + 2 * n, std::greater<int>());

  vector<pair<int, int>> result;
  for (int i = 1; i < 2 * n; ++i) {
    if (check(i, n, result)) {
      printf("YES\n");
      printf("%d\n", result.front().first + result.front().second);
      for (auto [x, y]: result) {
        printf("%d %d\n", x, y);
      }
      return;
    }
  }
  printf("NO\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
