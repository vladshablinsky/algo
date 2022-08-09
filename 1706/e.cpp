#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

using Range = pair<int, int>;

const int kMaxN = 100005;

struct DsuNode {
  // set of ranges e.g. (1, 2), (5, 5) ...
  set<Range> st;
  int rank;
  int sz;
  int p;
} nodes[kMaxN];

void dsu_prepare(int n) {
  for (int i = 0; i < n; ++i) {
    nodes[i] = {{{i, i}}, 1, 1, i};
  }
}

int dsu_find(int x) {
  // looped
  if (nodes[x].p == x) {
    return nodes[x].p;
  }

  return nodes[x].p = dsu_find(nodes[x].p);
}

vector<Range> merge_sets(set<Range> &trg, const set<Range>& src) {
  vector<Range> new_ranges;

  for (auto [from, to]: src) {
    int l = from;
    int r = to;

    // first try to merge (from, to) with something to the left
    if (auto it = trg.lower_bound({from, 0}); it != trg.begin() && prev(it)->second + 1 == from) {
      l = prev(it)->first;
      trg.erase(prev(it));
    }

    // then see if (from, to) also can be merged to smth to the right
    if (auto it = trg.upper_bound({to, to}); it != trg.end() && it->first == to + 1) {
      r = it->second;
      trg.erase(it);
    }

    trg.insert({l, r});
    if (l != from || r != to) {
      new_ranges.push_back({l, r});
    }
  }
  return new_ranges;
}

// returns new segments
vector<Range> dsu_unite(int a, int b) {
  vector<Range> result;
  a = dsu_find(a);
  b = dsu_find(b);

  if (a != b) {
    if (nodes[a].rank < nodes[b].rank) {
      swap(a, b);
    }
    nodes[b].p = a;
    nodes[a].rank += nodes[b].rank;

    //cout << "LINK " << b << " to " << a << endl;
    if (nodes[a].st.size() < nodes[b].st.size()) {
      swap(nodes[a].st, nodes[b].st);
    }
    auto& big = nodes[a].st;
    auto& small = nodes[b].st;

    result = std::move(merge_sets(big, small));
  }
  return result; // rvo
}

struct WalkableRange {
  int l;
  int r;
  int cost;
  bool operator<(const WalkableRange& other) const {
    if (l == other.l) {
      if (r == other.r) {
        return cost < other.cost;
      }
      return r < other.r;
    }
    return l < other.l;
  }
};

void solve() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);

  dsu_prepare(n);
  vector<WalkableRange> segs;
  for (int i = 0; i < n; ++i) {
    segs.push_back({i, i, 0});
  }

  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, -- v;

    for (auto [l, r]: dsu_unite(u, v)) {
      //cout << "NEWS: " << l << "..." << r << " cost: " << i + 1 << endl;
      segs.push_back({l, r, i + 1});
    }
  }

  //cout << "SEGS INPUT\n";
  sort(segs.begin(), segs.end());

  vector<pair<Range, int>> queries;
  queries.reserve(q);
  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l, --r;
    queries.push_back({{l, r}, i});
  }
  sort(queries.begin(), queries.end(), [](auto e1, auto e2) {
    return e1.first < e2.first;
  });

  // Two pointers logic
  // One pointer points to the query, the other points to the range in segs
  // St's elements are {r, k} where r is the end of currently open segment
  // and k is the maximum edge so that all ...r are reachable
  set<pair<int, int>> st;
  vector<int> ans(q);
  int p2 = 0;
  for (auto& [range, q_id]: queries) {
    auto [l, r] = range;

    // closed
    while (st.size() && st.begin()->first < l) {
      st.erase(st.begin());
    }

    // pass through ended segments
    while (p2 < segs.size() && segs[p2].l <= l) {
      if (segs[p2].r >= l) {
        st.insert({segs[p2].r, segs[p2].cost});
      }
      ++p2;
    }

    // Now find the answer
    auto it = st.lower_bound({r, 0});
    //cout << "ans for this query: " << it->second << " and seg: " << it->first << endl;
    ans[q_id] = it->second;
  }

  //cout << "ANSWER:\n";
  for (auto e: ans) {
    printf("%d ", e);
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
