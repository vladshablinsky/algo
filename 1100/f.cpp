#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int BITS_CNT = 20;
const int MAXN = 500005;

struct Query {
  int l, r;
  int id;
};

vector<Query> queries;
vector<int> ans;
vector<int> burger_cost;
vector<vector<int>> basises;
int n;

void print_basis(vector<int> &bs) {
  cout << "{";
  for (auto el: bs) {
    cout << el << ",";
  }
  cout << "}\n";
}

void add_to_basis(vector<int> &bs, int element) {
  if (bs.empty()) {
    bs.push_back(element);
    return;
  }

  int cur_i = 0;
  for (int j = BITS_CNT - 1; j >= 0; --j) {
    bool is_el_set = ((1 << j) & element);
    bool is_bs_set = ((1 << j) & bs[cur_i]);

    if (is_el_set && !is_bs_set) {
      // Linear independent for sure.
      bs.insert(bs.begin() + cur_i, element);
      return;
    } else if (is_bs_set) {
      if (is_el_set) {
        element ^= bs[cur_i];
      }
      // Iterate to next vector. It must be:
      // a) Less
      // b) Have first j bits unset
      ++cur_i;
    }

    if (cur_i == bs.size()) {
      if (element) {
        bs.push_back(element);
      }
      return;
    }
  }
}

int get_ans_from_basis(vector<int> bs) {
  int ans = 0;
  for (auto el: bs) {
    ans = max(ans, ans ^ el);
  }
  return ans;
}

void solve(int l, int r, vector<Query> &queries) {
  if (l > r) {
    return;
  }

  int mid = (l + r) / 2;
  vector<int> prev;
  prev.reserve(BITS_CNT);
  for (int i = mid; i >= l; --i) {
    add_to_basis(prev, burger_cost[i]);
    basises[i] = prev;
  }

  prev.clear();
  for (int i = mid + 1; i <= r; ++i) {
    add_to_basis(prev, burger_cost[i]);
    basises[i] = prev;
  }

  vector<Query> left_q;
  vector<Query> right_q;
  for (auto &q: queries) {
    if (q.r < mid) {
      left_q.push_back(q);
    } else if (q.l > mid + 1) {
      right_q.push_back(q);
    } else {
      vector<int> left_bs;
      if (q.l <= mid) {
        left_bs = basises[q.l];
      }
      vector<int> right_bs;
      if (q.r >= mid + 1) {
        right_bs = basises[q.r];
      }

      if (left_bs.size() < right_bs.size()) {
        swap(left_bs, right_bs);
      }
      for (auto el: right_bs) {
        add_to_basis(left_bs, el);
      }
      ans[q.id] = get_ans_from_basis(left_bs);
    }
  }

  solve(l, mid - 1, left_q);
  solve(mid + 2, r, right_q);
}

int main() {
  scanf("%d", &n);
  burger_cost.resize(n);
  basises.resize(n);
  ans.resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &burger_cost[i]);
  }

  int q;
  scanf("%d", &q);
  ans.resize(q);
  queries.resize(q);
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    queries[i].l = l - 1;
    queries[i].r = r - 1;
    queries[i].id = i;
  }

  solve(0, n - 1, queries);
  for (auto cur_ans: ans) {
    printf("%d\n", cur_ans);
  }
  return 0;
}
