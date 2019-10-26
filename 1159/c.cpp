#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  long long sum = 0;
  bool no_ans = false;

  vector<int> b(n);
  int used_cnt = 0;
  int max_b = 0;

  for (int i = 0; i < n; ++i) {
    cin >> b[i];
    max_b = max(max_b, b[i]);
    sum += b[i] * 1ll * m;
  }
  sort(b.begin(), b.end());

  for (int j = 0; j < m; ++j) {
    int cur_g;
    cin >> cur_g;
    if (cur_g < max_b) {
      no_ans = true;
      break;
    }

    if (used_cnt == m - 1) {
      b.pop_back();
      used_cnt = 0;
    }

    if (b.empty()) {
      no_ans = true;
      break;
    }

    if (cur_g == max_b) {
      continue;
    }

    sum += (cur_g - b.back());
    ++used_cnt;
  }

  if (no_ans) {
    sum = -1;
  }
  cout << sum << "\n";
  return 0;
}
