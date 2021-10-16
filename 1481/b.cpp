#include <iostream>
#include <vector>

using namespace std;

const int INF = 105;

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  vector<pair<int, int>> v;
  v.push_back({INF, -1});
  int ans = -1;

  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);

    // when this is true, the size of the stack is always >= 2
    while (k && v.back().first < el) {
      int h_diff = min(next(v.rbegin())->first, el) - v.rbegin()->first;
      int w_diff = i - next(v.rbegin())->second - 1;

      // cout << "h_diff: "<< h_diff <<", w_diff " << w_diff << endl;

      if (k && h_diff * w_diff >= k) {
        // if k % w_diff == 0, then k is w_diff;
        // otherwise k
        //  cout << "FINISHING" << endl;

        ans = i - (k - 1) % w_diff;
        k = 0;
        break;
      } else {
        k -= h_diff * w_diff;
        // cout << "k -= " << h_diff * w_diff << ": " << k <<  endl;
      }
      v.pop_back();
    }

    // if back == el skip
    if (el != v.back().first) {
      // cout << "push " << el << endl;
      v.push_back({el, i});
    } else {
      v.back().second = i;
    }
  }

  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
