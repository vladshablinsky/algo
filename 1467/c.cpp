#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 3;
const int INF = 1000000000;
int cnt[N];
int mns[N];

int main() {
  for (int i = 0; i < N; ++i) {
    scanf("%d", &cnt[i]);
  }

  long long sum = 0;
  long long min_exclude = INF * 1ll * INF;
  for (int i = 0; i < N; ++i) {
    mns[i] = INF;
    long long cur_cost = 0;
    int el;
    for (int j = 0; j < cnt[i]; ++j) {
      scanf("%d", &el);
      cur_cost += el;
      mns[i] = min(el, mns[i]);
    }
    sum += cur_cost;
    min_exclude = min(min_exclude, 2 * cur_cost);
  }
  sort(mns, mns + N);
  min_exclude = min(min_exclude, 2 * 1ll * (mns[0] + mns[1]));
  cout << sum - min_exclude << "\n";
}
