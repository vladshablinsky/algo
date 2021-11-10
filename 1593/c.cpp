#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 400005;

int solve() {
  vector<int> v;
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < k; ++i) {
    int el;
    scanf("%d", &el);
    v.push_back(el);
  }

  sort(v.begin(), v.end(), std::greater<int>());

  int cur_x = 0;
  int ans = 0;
  for (auto el: v) {
    if (el > cur_x) {
      // cout << "el: " << el << ", cur_x: " << cur_x << endl;
      ++ans;
      cur_x += (n - el);
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
