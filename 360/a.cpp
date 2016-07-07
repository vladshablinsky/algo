#include <iostream>
#include <cstdio>

using namespace std;

int a[105][105];

int main() {
  int n;
  int d;
  scanf("%d%d", &n, &d);
  int ans = 0;
  int cur_ans = 0;
  for (int i = 0; i < d; ++i) {
    string s;
    cin >> s;
    int cnt = 0;
    for (int j = 0; j < n; ++j) {
      cnt += (s[j] == '1');
    }
    if (cnt == n) {
      ans = max(ans, cur_ans);
      cur_ans = 0;
    } else {
      ++cur_ans;
    }
  }

  cout << max(ans, cur_ans) << "\n";
  return 0;
}
