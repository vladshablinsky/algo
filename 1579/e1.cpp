#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);
  deque<int> ans;
  int el;
  scanf("%d", &el);
  ans.push_back(el);
  for (int i = 1; i < n; ++i) {
    scanf("%d", &el);
    if (ans.front() < el) {
      ans.push_back(el);
    } else {
      ans.push_front(el);
    }
  }
  for (auto x: ans) {
    printf("%d ", x);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
