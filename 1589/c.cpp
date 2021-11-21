#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

bool solve() {
  int n;
  scanf("%d", &n);
  multiset<int> a;
  vector<int> b(n);

  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    a.insert(el);
  }

  for (auto& el: b) {
    scanf("%d", &el);
  }

  sort(b.begin(), b.end(), std::greater<int>());
  for (auto el: b) {
    if (auto it = a.find(el); it != a.end()) {
      a.erase(it);
    } else if (auto it = a.find(el - 1); it != a.end()) {
      a.erase(it);
    } else {
      return false;
    }
  }
  return true;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
