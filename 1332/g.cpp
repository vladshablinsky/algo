#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int a[MAXN];
vector<int> no_seq_dups_idx;
vector<pair<int, int>> peaks;

void solve(int l, int r) {
  // find first peak at [l...]
  // find first peak at [r + 1, ...]. This peak should not be included.
  auto lit = lower_bound(peaks.begin(), peaks.end(), pair<int, int>{l, 0});
  auto rit = lower_bound(peaks.begin(), peaks.end(), pair<int, int>{r + 1, 0});

  // cout << "LIT: " << lit->first << endl;
  // cout << "RIT: " << rit->first << endl;

  vector<int> ans;
  if (lit != peaks.end()) {
    // previous peak is out of range, but previous elemenant may not be.
    if (lit->second && no_seq_dups_idx[lit->second - 1] >= l) {
      ans.push_back(no_seq_dups_idx[lit->second - 1]);
    }

    cout << rit - lit << endl;
    for (auto it = lit; it != rit && ans.size() < 4; ++it) {
      //cout << "cur number: " << a[it->first] << endl;
      ans.push_back(it->first);

      // next peak is out of range, but next element may not be.
      if (ans.size() < 4 && next(it) == rit && it->second + 1 < no_seq_dups_idx.size() &&
          no_seq_dups_idx[it->second + 1] <= r) {
        ans.push_back(no_seq_dups_idx[it->second + 1]);
      }
    }
  }

  if (ans.size() > 2) {
    printf("%d\n", (int)ans.size());
    for (auto el: ans) {
      printf("%d ", el);
    }
    printf("\n");
  } else {
    printf("0\n");
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);

  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (a[i] == a[i - 1]) {
      continue;
    }
    no_seq_dups_idx.push_back(i);
  }

  if (no_seq_dups_idx.size()) {
    peaks.emplace_back(no_seq_dups_idx.front(), 0);
    for (int i = 1; i + 1 < no_seq_dups_idx.size(); ++i) {
      int cur_idx = no_seq_dups_idx[i];
      int prev_idx = no_seq_dups_idx[i - 1];
      int next_idx = no_seq_dups_idx[i + 1];
      if ((a[cur_idx] > a[prev_idx] && a[cur_idx] > a[next_idx]) ||
          (a[cur_idx] < a[prev_idx] && a[cur_idx] < a[next_idx])) {
        peaks.emplace_back(cur_idx, i);
      }
    }
    if (no_seq_dups_idx.size() > 1) {
      peaks.emplace_back(no_seq_dups_idx.back(), no_seq_dups_idx.size() - 1);
    }
  }

  cout << "peaks are: " << endl;
  for (auto idx: peaks) {
    cout << "(" << a[idx.first] << ", " << idx.second << "), ";
  }
  cout << endl;

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    solve(l, r);
  }
  return 0;
}
