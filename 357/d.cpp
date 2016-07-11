#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

using namespace std;

const int MAX_N = 1e5 + 5;

int parent[MAX_N];
int used[MAX_N];
int a[MAX_N];
int components[MAX_N];
int last_resorts[MAX_N];
int cur_component = 0;
vector<int> g[MAX_N];
vector<deque<int> > ans;
int n, m;

void dfs(int v) {
  used[v]= true;
  components[v] = cur_component;

  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to]) {
      dfs(to);
    }
  }
}

void dfs_ex(int v, int ok_tree_head) {
  used[v] = true;

  if (v == ok_tree_head) {
    return;
  }
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to]) {
      dfs_ex(to, ok_tree_head);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);

  for (int i = 0; i < m; ++i) {
    int dad, son;
    scanf("%d%d", &dad, &son);
    --dad, --son;
    parent[son] = dad;
    g[dad].push_back(son);
    g[son].push_back(dad);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    --a[i];
  }

  // split into components;
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      ans.push_back(deque<int>());
      dfs(i);
      ++cur_component;
    }
  }

  for (int i = 0; i < n; ++i) {
    used[i] = false;
  }

  //for (int i = 0; i < n; ++i) {
    //cout << components[i] << " ";
  //}
  //cout << endl;

  for (int i = 0; i < n; ++i) {
    //cout << "INSPECTING I = " << i << endl;
    cur_component = components[i];

    if (used[a[i]] || used[i]) {
      if (a[i] != ans[cur_component].front()) {
        printf("-1\n");
        return 0;
      } else {
        continue;
      }
    }

    ans[cur_component].push_front(a[i]);
    dfs_ex(a[i], i);

    ////cout << "USED IS \n";
    //for (int i = 0; i < n; ++i) {
      //cout << used[i] << " ";
    //}
    //cout << endl;
  }

  int sum = 0;
  for (int i = 0; i < ans.size(); ++i) {
    sum += ans[i].size();
  }
  printf("%d\n", sum);
  for (int i = 0; i < ans.size(); ++i) {
    for (auto it = ans[i].begin(); it != ans[i].end(); ++it) {
      printf("%d\n", *it + 1);
    }
  }
  return 0;
}

