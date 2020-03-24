#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 200005;

int a[MAXN];
bool used[MAXN];
vector<int> g[MAXN];
int sieve[MAXN];
int ans = 0;

void make_sieve() {
  for (int i = 2; i * i < MAXN; ++i) {
    if (!sieve[i]) {
      for (int j = i * i; j < MAXN; j += i) {
        sieve[j] = i;
      }
    }
  }
}

unordered_map<int, int> dfs(int v) {
  used[v] = true;
  vector<unordered_map<int, int>> children;
  for (auto to: g[v]) {
    if (!used[to]) {
      children.emplace_back(std::move(dfs(to)));
    }
  }

  unordered_map<int, int> v_divs;
  int cur_i;
  for (cur_i = a[v]; sieve[cur_i]; cur_i /= sieve[cur_i]) {
    v_divs[sieve[cur_i]] = 1;
  }
  if (cur_i != 1) {
    v_divs[cur_i] = 1;
  }

  //cout << "in vertex " << v << endl;
  for (auto &el: v_divs) {
    //cout << "checking div " << el.first << endl;
    pair<int, int> max_children = {0, 0};
    for (auto &child_divs: children) {
      if (child_divs.count(el.first)) {
        int cnt_els_subtree = child_divs[el.first];
        //cout << "in subtree res is " << cnt_els_subtree << endl;
        el.second = max(el.second, 1 + cnt_els_subtree);

        max_children.first = max(max_children.first, cnt_els_subtree);
        if (max_children.first > max_children.second) {
          swap(max_children.first, max_children.second);
        }
      }
    }
    ans = max(ans, max_children.first + max_children.second + 1);
    //cout << "RES ans:" << ans << endl;
  }
  return v_divs;
}

int main() {
  make_sieve();
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from; --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }
  //cout << "READ\n";
  dfs(0);
  printf("%d\n", ans);
  return 0;
}
