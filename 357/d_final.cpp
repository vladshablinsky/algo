#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 1e5 + 5;

vector<int> g[MAX_N];
bool used[MAX_N];
bool guys_with_presents[MAX_N];
int should_give_to[MAX_N];
int actually_gives_to[MAX_N];
vector<int> top;
vector<int> ans;
int n, m, k;

void init_used() {
  for (int i = 0; i < MAX_N; ++i) {
    used[i] = false;
  }
}

void topsort(int v) {
  used[v] = true;
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to]) {
      topsort(to);
    }
  }
  top.push_back(v);
}

void dfs(int v, int present_receiver) {
  used[v] = true;
  actually_gives_to[v] = present_receiver;
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to]) {
      dfs(to, present_receiver);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int p, q;
    scanf("%d%d", &p, &q);
    --p;
    --q;
    g[p].push_back(q);
  }

  for (int i = 0; i < n; ++i) {
    int to;
    scanf("%d", &to);
    --to;
    should_give_to[i] = to;
    guys_with_presents[to] = true;
  }

  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      topsort(i);
    }
  }

  //cout << "TOPSORT IS\n";
  //for (int i = 0; i < top.size(); ++i) {
    //cout << top[i] << " ";
  //}
  //cout << endl;

  // reverse(top.begin(), top.end());

  // Get the result sequence {ans}
  for (int i = 0; i < top.size(); ++i) {
    if (guys_with_presents[top[i]]) {
      ans.push_back(top[i]);
    }
  }

  //cout << "ANS IS\n";
  //for (int i = 0; i < ans.size(); ++i) {
    //cout << ans[i] << " ";
  //}
  //cout << endl;

  init_used();
  for (int i = 0; i < ans.size(); ++i) {
    if (!used[ans[i]]) {
      dfs(ans[i], ans[i]);
    }
  }

  for (int i = 0; i < n; ++i) {
    if (should_give_to[i] != actually_gives_to[i]) {
      printf("-1\n");
      return 0;
    }
  }

  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d\n", ans[i] + 1);
  }

  return 0;
}
