#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

void solve() {
  int n;
  vector<int> in;
  vector<int> idx_to_use;

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int p;
    scanf("%d", &p);
    in.emplace_back(p);
    idx_to_use.emplace_back(i);
  }
  sort(idx_to_use.begin(), idx_to_use.end(), [&](int i1, int i2) {
      return in[i1] < in[i2];
    }
  );

  vector<int> out;
  int last_used_idx = n;
  while (!idx_to_use.empty()) {
    for (int i = idx_to_use.back(); i < last_used_idx; ++i) {
      out.push_back(in[i]);
    }
    last_used_idx = idx_to_use.back();

    while (idx_to_use.size() && idx_to_use.back() >= last_used_idx) {
      idx_to_use.pop_back();
    }
  }

  for (auto el: out) {
    printf("%d ", el);
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
