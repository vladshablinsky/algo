#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int MAXN = 1e5 + 5;
int n;

unordered_map<int, unordered_multiset<int>> g;
int b[MAXN];
int c[MAXN];

int main() {
  vector<int> vs;
  scanf("%d", &n);

  for (int i = 0; i < n - 1; ++i) {
    scanf("%d", &b[i]);
  }
  for (int i = 0; i < n - 1; ++i) {
    scanf("%d", &c[i]);
  }

  for (int i = 0; i < n - 1; ++i) {
    if (b[i] > c[i]) {
      cout << "-1\n";
      return 0;
    }
    g[b[i]].insert(c[i]);
    if (c[i] != b[i]) {
      g[c[i]].insert(b[i]);
    }
  }

  int v1 = -1, v2= -1;
  for (auto &el: g) {
    int cur_v = el.first;
    int deg_cur_v = el.second.size() + el.second.count(cur_v);
    //cout << "deg of " << cur_v << " is " << deg_cur_v << endl;
    if (deg_cur_v & 1) {
      if (v1 == -1) {
        v1 = cur_v;
      } else if (v2 == -1) {
        v2 = cur_v;
      } else {
        cout << "-1\n";
        return 0;
      }
    }
  }

  // Add edge to find Euler's loop
  if (v1 != -1) {
    g[v1].insert(v2);
    g[v2].insert(v1);
    //cout << "v1: " << v1 << ", v2: " << v2 << endl;
  }

  vector<int> loop;
  vector<int> path;
  vector<int> st;

  // Add any vertex. Since all vertices have deg(v) >= 1 it's legal.
  st.push_back(g.begin()->first);
  while (!st.empty()) {
    int cur_v = st.back();

    //cout << "cur_v " << cur_v << endl;

    if (g[cur_v].empty()) {
      loop.push_back(cur_v);
      st.pop_back();

      //cout << "no edges from here left\n";
    } else {
      auto it = g[cur_v].begin();
      int u = *it;
      //cout << "go from " << cur_v << " to " << u << endl;
      st.push_back(u);
      g[cur_v].erase(it);
      if (cur_v != u) {
        g[u].erase(g[u].find(cur_v));
      }

      //cout << "now deg(" << cur_v <<  ") is " << g[cur_v].size() + g[cur_v].count(cur_v) << endl;
      //cout << "now deg(" << u <<  ") is " << g[u].size() + g[u].count(u) << endl;
    }
  }

  if (v1 != -1) {
    //cout << "LOOP\n";
    //for (auto &el: loop) {
    //  cout << el << " ";
    //}
    //cout << endl;

    for (int i = 0; i + 1 < loop.size(); ++i) {
      if ((loop[i] == v1 && loop[i + 1] == v2) || (loop[i] == v2 && loop[i + 1] == v1)) {
        for (int j = i + 1; j < loop.size(); ++j) {
          path.push_back(loop[j]);
        }
        for (int j = 1; j <= i; ++j) {
          path.push_back(loop[j]);
        }
        break;
      }
    }
  } else {
    path = std::move(loop);
  }

  // cout << "all good so far\n";

  // Some of the edges are in different component. No answer.
  for (auto &el: g) {
    if (!el.second.empty()) {
      cout << "-1\n";
      return 0;
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << path[i] << " ";
  }
  cout << "\n";
  return 0;
}
