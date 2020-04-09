#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <cstdio>
#include <deque>

using namespace std;

const int MAXN = 5002;
const long long INF = 1000000000 * 1ll * 1000000000;

template<typename T>
struct sliding_max {
  deque<pair<T, int>> dq;
  void push_back(T el, int pos) {
    while (dq.size() && dq.back().first < el) {
      dq.pop_back();
    }
    dq.emplace_back(el, pos);
  }

  void pop_front(int pos) {
    if (dq.size() && dq.front().second == pos) {
      dq.pop_front();
    }
  }

  bool empty() {
    return dq.empty();
  }

  T get_max() {
    return dq.front().first;
  }
};

int a[MAXN];
long long f[MAXN][MAXN];
sliding_max<long long> mst[MAXN];

int main() {
  int n, k, x;
  scanf("%d%d%d", &n, &k, &x);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < MAXN; ++i) {
    for (int j = 0; j < MAXN; ++j) {
      f[i][j] = -INF;
    }
  }
  f[0][0] = 0;
  mst[0].push_back(0, 0);

  long long ans = -1;
  long long max_prev_beauty_one_less_repost;
  multiset<long long>::iterator it;
  for (int i = 1; i <= n; ++i) {
    for (int j = x; j >= 0; --j) {
      max_prev_beauty_one_less_repost =
        (j - 1 >= 0 && !mst[j - 1].empty() ? mst[j - 1].get_max() : -INF);
      if (max_prev_beauty_one_less_repost != -INF) {
        f[i][j] = max_prev_beauty_one_less_repost + a[i];
        mst[j].push_back(f[i][j], i);
      }

      if (i - k >= 0) {
        mst[j].pop_front(i - k);
      }
    }
  }
  ans = max(ans, (mst[x].empty() ? -INF: mst[x].get_max()));
  cout << ans << "\n";
  return 0;
}
