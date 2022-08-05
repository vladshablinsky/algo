#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

vector<pair<int, int>> get_edges(vector<int>& prufer)
{
  vector<pair<int, int>> res;
  int vertices = prufer.size() + 2;
  vector<int> vertex_set(vertices, 0);

  for (auto v: prufer) {
    vertex_set[v - 1]++;
  }

  // Find the smallest label not present in prufer
  int j = 0;
  for (int i = 0; i < vertices - 2; i++) {
    for (j = 0; j < vertices; j++) {
      if (vertex_set[j] == 0) {
        vertex_set[j] = -1;
        res.push_back({j + 1, prufer[i]});
        vertex_set[prufer[i] - 1]--;
        break;
      }
    }
  }

  j = 0;
  for (int i = 0; i < vertices; i++) {
    if (vertex_set[i] == 0 && j == 0) {
      res.push_back({i + 1, 0});
      j++;
    }
    else if (vertex_set[i] == 0 && j == 1) {
      res.back().second = i + 1;
    }
  }
  for (auto& el: res) {
    if (el.second < el.first) {
      swap(el.first, el.second);
    }
  }
  return res;
}

void gen_graf_and_edges() {
  std::random_device rd;
  std::mt19937 g(rd());

  int n = 100;
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, n);


  // prufers code
  vector<int> code;
  vector<pair<int, int>> edges;
  for (int i = 0; i < n - 2; ++i) {
    code.push_back(dist(g));
  }
  edges = get_edges(code);

  set<pair<int, int>> unique_edges(edges.begin(), edges.end());
  for (int i = 0, mx = dist(g) * dist(g); i < mx; ++i) {
    int from = dist(g);
    int to = dist(g);
    if (from == to) {
      continue;
    }
    if (from > to) {
      swap(from, to);
    }
    unique_edges.insert({from, to});
  }

  edges.clear();
  for (auto el: unique_edges) {
    edges.push_back(el);
  }
  std::shuffle(edges.begin(), edges.end(), g);

  vector<pair<int, int>> qs(min(n * (n - 1) / 2, 100000));
  set<pair<int, int>> st;
  for (auto& el: qs) {
    do {
      el.first = dist(g);
      el.second = dist(g);
      if (el.first > el.second) {
        swap(el.first, el.second);
      }
    } while (st.count({el.first, el.second}));
    st.insert({el.first, el.second});
  }
  cout << n << " " << edges.size() << " " << qs.size() << endl;

  for (auto [s, f]: edges) {
    cout << s << " " << f << endl;
  }
  for (auto [s, f]: qs) {
    cout << s << " " << f << endl;
  }
}

int main() {
  // print part
  // cout
  cout << 1 << endl;
  gen_graf_and_edges();
}
