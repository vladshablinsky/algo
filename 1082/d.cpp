#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
  set<pair<int, int>, std::greater<pair<int, int>>> st;
  vector<int> leafs;
  vector<pair<int, int>> edges;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int max_deg;
    cin >> max_deg;
    if (max_deg == 1) {
      leafs.push_back(i);
    } else {
      st.insert(make_pair(max_deg - 2, i));
    }
  }

  auto prev_it = st.begin();
  if (prev_it != st.end()) {
    for (auto it = next(prev_it); it != st.end(); it++) {
      edges.push_back(make_pair(prev_it->second + 1, it->second + 1));
      prev_it = it;
    }
  }

  if (n == 2) {
    cout << "YES 2\n";
    cout << "1\n";
    cout << "1 2\n";
  } else if (leafs.empty()) {
    cout << "YES " << n - 1 << "\n";
    cout << n - 1 << "\n";
    for (int i = 0; i < n - 1; ++i) {
      cout << i + 1 << " " << i + 2 << "\n";
    }
  } else {
    int ans = max(0, (int)st.size() - 1);
    int first;
    int last;

    if (st.size() == 1) {
      first = last = st.begin()->second + 1;
    } else if (st.size() > 1) {
      first = edges.front().first;
      last = edges.back().second;
    } else {
      cout << "NO\n";
      return 0;
    }

    if (leafs.size() > 1) {
      ans += 2;
      edges.push_back(make_pair(leafs[0] + 1, first));
      edges.push_back(make_pair(leafs[1] + 1, last));
    } else {
      ++ans;
      edges.push_back(make_pair(leafs[0] + 1, first));
    }

    for (int i = 2; i < leafs.size(); ++i) {
      if (!st.empty() && st.begin()->first != 0) {
        auto cur = *st.begin();
        edges.push_back(make_pair(leafs[i] + 1, cur.second + 1));
        cur.first--;
        st.erase(st.begin());
        st.insert(cur);
      } else {
        cout << "NO\n";
        return 0;
      }
    }
    cout << "YES " << ans << "\n";
    cout << edges.size() << "\n";
    for (auto edge: edges) {
      cout << edge.first << " " << edge.second << "\n";
    }
  }
  return 0;
}
