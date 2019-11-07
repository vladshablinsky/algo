#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 200005;

vector<int> g_0[MAX_N];
vector<int> g_1[MAX_N];
bool used_0[MAX_N];
bool used_1[MAX_N];
int component_0[MAX_N];
int component_1[MAX_N];
int comp_sizes[2 * MAX_N];
int cur_component = 0;

int dfs(int v, bool use_0=true) {
  bool *used = (use_0 ? used_0 : used_1);
  int *component = (use_0 ? component_0 : component_1);
  used[v] = true;
  int comp_size = 1;
  component[v] = cur_component;

  auto &g = (use_0 ? g_0 : g_1);
  for (auto to: g[v]) {
    if (!used[to]) {
       comp_size += dfs(to, use_0);
    }
  }
  return comp_size;
}


int main() {
  long long ans = 0;
  int n;

  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to, cost;
    scanf("%d%d%d", &from, &to, &cost);
    --from; --to;
    if (cost) {
      g_1[from].push_back(to);
      g_1[to].push_back(from);
    } else {
      g_0[from].push_back(to);
      g_0[to].push_back(from);
    }
  }

  for (int i = 0; i < n; ++i) {
    int size_0 = 1;
    int size_1 = 1;
    if (!used_0[i]) {
      //cout << "new ZERO component from " << i << endl;
      ++cur_component;
      size_0 = comp_sizes[cur_component] = dfs(i, true);
      ans += (comp_sizes[cur_component] * 1ll * (comp_sizes[cur_component] - 1));
    } else {
      size_0 = comp_sizes[component_0[i]];
    }

    //cout << "size of ZERO component in " << i << " is " << size_0 << endl;

    if (!used_1[i]) {
      //cout << "new ONE component from " << i << endl;
      ++cur_component;
      size_1 = comp_sizes[cur_component] = dfs(i, false);
      ans += (comp_sizes[cur_component] * 1ll * (comp_sizes[cur_component] - 1));
    } else {
      size_1 = comp_sizes[component_1[i]];
    }
    //cout << "size of ONE component in " << i << " is " << size_1 << endl;

    ans += ((size_0 - 1) * 1ll * (size_1 - 1));
  }
  cout << ans << "\n";
  return 0;
}
