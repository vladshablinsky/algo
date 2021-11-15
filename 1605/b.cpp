#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  int n;
  string s;

  scanf("%d", &n);
  cin >> s;

  int cnt_zeros = 0;
  for (auto c: s) {
    cnt_zeros += (c == '0');
  }

  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    if (s[i] == '1' && i < cnt_zeros) {
      ans.push_back(i);
    }
    if (s[i] == '0' && i >= cnt_zeros) {
      ans.push_back(i);
    }
  }

  if (ans.empty()) {
    printf("0");
  } else {
    printf("1\n%d ", ans.size());
    for (auto el: ans) {
      printf("%d ", el + 1);
    }
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
