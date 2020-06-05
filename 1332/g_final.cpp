#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>

using namespace std;

const int MAXN = 200005;
const int INF = 1e9;
int a[MAXN];
vector<int> four_chains[MAXN];
vector<int> three_chains[MAXN];

void squeeze(int n) {
  map<int, int> mp;
  for (int i = 1; i <= n; ++i) {
    mp[a[i]];
  }
  int mapped_val = 1;
  for (auto &el: mp) {
    el.second = mapped_val++;
  }
  for (int i = 1; i <= n; ++i) {
    a[i] = mp[a[i]];
    printf("%2d|", a[i]);
  }
  cout << endl;
  for (int i = 1; i <= n; ++i) {
    printf("%2d|", i);
  }
  cout << endl;
}

void precalc(int n) {
  // st_inc -- stack of indices from a going right to left so
  // that st_inc[i] value is greater or equal than st_inc[i - 1] value
  // AND st_inc[i - 1] is the closest index from st_inc[i] meeting
  // that condition. st_inc.back() is always currently processed index.
  vector<int> st_inc;
  vector<int> st_dec;

  unordered_set<int> inc_indices;
  unordered_set<int> dec_indices;
  set<int> excluded_indices; // indices that are no longer in stacks.
  int longest_inc_chain = 0;
  int longest_dec_chain = 0;
  int best_right_four_chain_idx = 0;
  int best_right_three_chain_idx = 0;

  for (int i = n; i >= 0; --i) {
    // a[i] should be the greatest element among st_inc index values.
    int back_idx;
    while (st_inc.size() && a[back_idx = st_inc.back()] > a[i]) {
      longest_inc_chain = 0;
      inc_indices.erase(back_idx);
      if (!dec_indices.count(back_idx)) {
        excluded_indices.insert(back_idx);
      }
      st_inc.pop_back();
    }

    while (st_dec.size() && a[back_idx = st_dec.back()] < a[i]) {
      longest_dec_chain = 0;
      dec_indices.erase(back_idx);
      if (!inc_indices.count(back_idx)) {
        excluded_indices.insert(back_idx);
      }
      st_dec.pop_back();
    }

    // in st_inc a's values increase as we go from begin to end. As soon
    // as a[i] value can repeat, we need to find mostright index of it, which
    // will be mostleft index in the stack for that value. Note, that if
    // there is no chained values equal to a[i], we'll just point to
    // st_inc.end().
    // Basically we're finding iterator to the first value so that it
    // does not compare less to a[i], thus >= a[i].
    if (st_inc.size() && st_dec.size()) {
      //cout << "process for a[" << i << "]=" << a[i] << endl;

      auto start_st_inc = lower_bound(st_inc.begin(), st_inc.end(), i, [](int i1, int i2) {
          return a[i1] < a[i2];
          });
      int shift_in_inc = st_inc.end() - start_st_inc;

      auto start_st_dec = lower_bound(st_dec.begin(), st_dec.end(), i, [](int i1, int i2) {
          return a[i1] > a[i2];
          });
      int shift_in_dec = st_dec.end() - start_st_dec;

      int max_st_index = max(*(st_inc.rbegin() + shift_in_inc),
          *(st_dec.rbegin() + shift_in_dec));
      auto closing_idx_it = excluded_indices.lower_bound(max_st_index);
      if (closing_idx_it != excluded_indices.end()) {
        // find closest indices that are less than closing_idx
        // st_inc and st_dec has indices in descending order. So finding first that is
        // not std::greater.
        if (best_right_four_chain_idx &&
            four_chains[best_right_four_chain_idx].back() < *closing_idx_it) {
          four_chains[i] = four_chains[best_right_four_chain_idx];
        } else {
          int idx_mid_1 = *lower_bound(
              st_inc.begin(), st_inc.end(), *closing_idx_it, greater<int>());
          int idx_mid_2 = *lower_bound(
              st_dec.begin(), st_dec.end(), *closing_idx_it, greater<int>());
          four_chains[i] = {i, min(idx_mid_1, idx_mid_2), max(idx_mid_1, idx_mid_2), *closing_idx_it};
          best_right_four_chain_idx = i;
        }
      }
    }

    if (i + max(longest_inc_chain, longest_dec_chain) + 1 <= n) {
      int closing_idx = i + max(longest_inc_chain, longest_dec_chain) + 1;
      if (best_right_three_chain_idx &&
          three_chains[best_right_three_chain_idx].back() < closing_idx) {
        three_chains[i] = three_chains[best_right_three_chain_idx];
      } else {
        three_chains[i] = {i, closing_idx - 1, closing_idx};
        best_right_three_chain_idx = i;
      }
    }

    if (best_right_four_chain_idx && four_chains[i].empty()) {
      four_chains[i] = four_chains[best_right_four_chain_idx];
    }

    st_inc.push_back(i);
    inc_indices.insert(i);
    ++longest_inc_chain;

    st_dec.push_back(i);
    dec_indices.insert(i);
    ++longest_dec_chain;
  }
}

void print_vector(const vector<int> &v) {
  printf("%d\n", (int)v.size());
  for (auto el: v) {
    printf("%d ", el);
  }
  printf("\n");
}

void solve(int l, int r) {
  if (four_chains[l].size() && four_chains[l].back() <= r) {
    print_vector(four_chains[l]);
  } else if (three_chains[l].size() && three_chains[l].back() <= r) {
    print_vector(three_chains[l]);
  } else {
    printf("0\n");
  }
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  //squeeze(n);
  precalc(n);

  while (q--) {
    int l, r;
    scanf("%d%d", &l, &r);
    solve(l, r);
  }
  return 0;
}
