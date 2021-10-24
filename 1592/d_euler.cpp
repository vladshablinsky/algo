#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 1005;
vector<int> g[MAXN];
vector<int> euler_traversal;

void dfs(int v, int p) {
  euler_traversal.push_back(v);
  for (auto to: g[v]) {
    if (to != p) {
      dfs(to, v);
      euler_traversal.push_back(v);
    }
  }
}

int query_range(int l, int r) {
  cout << "? ";
  set<int> vertices;
  for (int i = l; i <= r; ++i) {
    vertices.insert(euler_traversal[i]);
  }
  cout << vertices.size() << " ";
  for (auto v: vertices) {
    cout << v << " ";
  }
  cout << "\n";

  int ans;
  cin >> ans;
  return ans;
}

void ans(int a, int b) {
  cout << "! " << a << " " << b << "\n";
  cout.flush();
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    cin >> from >> to;
    g[from].push_back(to);
    g[to].push_back(from);
  }


  dfs(1, 0);

  int l = 0;
  int r = euler_traversal.size() - 1;
  int target = query_range(l, r);
  while (r - l > 1) {
    // till while condition holds m is never equal to l
    int m = (r + l) / 2;

    if (query_range(l, m) == target) {
      r = m;
    } else {
      l = m;
    }
  }
  ans(euler_traversal[l], euler_traversal[l + 1]);
}
