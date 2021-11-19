#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
  int n;
  scanf("%d", &n);

  vector<int> v(n);
  string rbs;
  for (auto& el: v) {
    scanf("%d", &el);
  }
  cin >> rbs;
  vector<int> inc;
  vector<int> dec;
  for (int i = 0; i < n; ++i) {
    if (rbs[i] == 'B') {
      dec.push_back(v[i]);
    } else {
      inc.push_back(v[i]);
    }
  }
  sort(dec.begin(), dec.end());
  sort(inc.begin(), inc.end(), std::greater<int>());

  int i = 1;
  for (auto el: dec) {
    if (el < i) {
      return false;
    }
    ++i;
  }

  i = n;
  for (auto el: inc) {
    if (el > i) {
      return false;
    }
    --i;
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
