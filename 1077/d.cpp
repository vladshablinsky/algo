#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXS = 200005;
int cnt[MAXS];

int main() {
  int n, k;
  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    int a_i;
    scanf("%d", &a_i);
    cnt[a_i]++;
  }

  auto cmp = [](const pair<int, int> &a, const pair<int, int> &b) {
    return (cnt[a.first] / a.second) < (cnt[b.first] / b.second);
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

  for (int i = 0; i < MAXS; ++i) {
    if (cnt[i]) {
      pq.emplace(i, 1);
    }
  }

  for (int i = 0; i < k; ++i) {
    auto el = pq.top();
    pq.pop();

    printf("%d ", el.first);
    if (cnt[el.first] / (el.second + 1)) {
      pq.emplace(el.first, el.second + 1);
    }
  }
  printf("\n");
  return 0;
}
