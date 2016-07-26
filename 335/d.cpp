#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAX_N = 1e5 + 5;

long long pref[MAX_N];
set<pair<long long, pair<int, int>>> st;
vector<pair<long long, pair<int, int>>> ans;
int n, m;

vector<pair<int, int>> edges_in_tree;
vector<pair<int, int>> edges_not_in_tree;

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < m; ++i) {
    int cost, type;
    scanf("%d%d", &cost, &type);
    if (type) {
      edges_in_tree.push_back(make_pair(cost, i + 1));
    } else {
      edges_not_in_tree.push_back(make_pair(cost, i + 1));
    }
  }

  sort(edges_in_tree.begin(), edges_in_tree.end());
  sort(edges_not_in_tree.begin(), edges_not_in_tree.end());

  for (int i = 0; i < edges_in_tree.size(); ++i) {
    pref[i + 2] = pref[i + 1] + edges_in_tree[i].first;
  }

  for (int i = 1; i + 2 <= n; ++i) {
    st.insert(make_pair(pref[i + 2] - pref[i], make_pair(i, i + 2)));
  }

  while (ans.size() != m - n + 1) {
    auto it = st.begin();
    ans.push_back(*it);
    int from = it->second.first;
    int to = it->second.second;
    if (to + 1 <= n) {
      st.insert(make_pair(pref[to + 1] - pref[from], make_pair(from, to + 1)));
    }
    st.erase(st.begin());
  }

  for (int i = 0; i < m - n + 1; ++i) {
    if (ans[i].first > edges_not_in_tree[i].first) {
      cout << "-1\n";
      return 0;
    }
  }

  vector<pair<int, pair<int, int>>> result;
  for (int i = 0; i < n - 1; ++i) {
    result.push_back(make_pair(edges_in_tree[i].second, make_pair(i + 1, i + 2)));
  }

  for (int i = 0; i < m - n + 1; ++i) {
    result.push_back(make_pair(edges_not_in_tree[i].second, ans[i].second));
  }

  sort(result.begin(), result.end());

  for (auto x: result) {
    printf("%d %d\n", x.second.first, x.second.second);
  }
  return 0;
}
