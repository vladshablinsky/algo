#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int kInf = 1000000000;

bool solve() {
  string s;
  cin >> s;
  int n = s.length();
  vector<int> v(n, 0);
  // know it's lame
  vector<bool> is_wildcard(n, false);
  vector<int> lr_bals(n);

  int overall_balance = 0;
  int wildcards = 0;
  for (int i = 0; i < n; ++i) {
    auto c = s[i];
    if (c == '(') {
      v[i] = 1;
    } else if (c == ')') {
      v[i] = -1;
    } else {
      is_wildcard[i] = true;
      ++wildcards;
    }
    overall_balance += v[i];
  }

  // We know that one solition exists, so no need in checking
  int close_wld = (overall_balance + wildcards) / 2;
  int open_wld = wildcards - close_wld;

  if (!close_wld || !open_wld) {
    return true;
  }

  int first_close_wildcard_i = 0;
  overall_balance = 0;
  for (int i = 0, cnt = open_wld; i < v.size(); ++i) {
    if (is_wildcard[i]) {
      if (cnt) {
        --cnt;
        v[i] = 1;
      } else {
        if (!first_close_wildcard_i) {
          first_close_wildcard_i = i;
        }
        v[i] = -1;
      }
    }
    overall_balance += v[i];
    lr_bals[i] = overall_balance;
  }

  vector<int> min_rl_bal(first_close_wildcard_i + 2, kInf);
  vector<int> min_lr_bal(first_close_wildcard_i + 1, kInf);

  for (int i = n - 1, cur_bal = 0; i >= 0; --i) {
    cur_bal -= v[i];

    if (i <= first_close_wildcard_i) {
      min_rl_bal[i] = min(min_rl_bal[i + 1], cur_bal);
    }

    if (i < first_close_wildcard_i) {
      min_lr_bal[i] = min(min_lr_bal[i + 1], lr_bals[i]);
    }
  }

  for (int i = 0, cnt = open_wld; i < n && cnt; ++i) {
    if (is_wildcard[i]) {
      --cnt;
    }

    if (min_rl_bal[i + 1] > 1 && min_lr_bal[i] > 1) {
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
