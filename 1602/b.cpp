#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

const int MAXN = 1005;

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> at_step;
  at_step.push_back({});
  at_step.back().resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &at_step.back()[i]);
  }

  bool any_change = true;
  while (any_change) {
    auto& prev = at_step.back();
    any_change = false;
    map<int, int> freqs;
    for (auto el: prev) {
      freqs[el]++;
    }
    vector<int> last_row(n);
    for (int i = 0; i < n; ++i) {
      last_row[i] = freqs[prev[i]];
      if (last_row[i] != prev[i]) {
        any_change = true;
      }
    }

    if (any_change) {
      at_step.push_back(std::move(last_row));
    }
  }

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int k, x;
    scanf("%d%d", &x, &k);
    printf("%d\n", at_step[min(k, (int)at_step.size() - 1)][x - 1]);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
