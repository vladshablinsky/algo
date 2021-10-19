#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 500005;
const int IMP = 1;
const int CREW = 2;

vector<pair<int, bool>> g[MAXN];
int used[MAXN];

bool is_imposter(const string& s) {
  return s[0] == 'i';
}

bool is_imposter(int val) {
  return val == IMP;
}

int get_val(bool is_imp) {
  return is_imp ? IMP : CREW;
}

int get_other(bool slf, bool is_imp) {
  return get_val(slf ^ is_imp);
}

int dfs(int v, int assign_val, int p, bool& ok, vector<int> &vertices) {
  if (!ok) {
    return 0;
  }

  // cout << "dfs " << v << ", val: " << assign_val << endl;

  used[v] = assign_val;
  vertices.push_back(v);
  int cnt_imposters_subtree = 0;
  bool is_imp_v = is_imposter(used[v]);
  for (auto [to, is_imp]: g[v]) {
    int to_assign_val = get_other(is_imp_v, is_imp);
    if (used[to] && used[to] != to_assign_val) {
      ok = false;
      return 0;
    }

    if (to != p && !used[to]) {
      cnt_imposters_subtree += dfs(to, to_assign_val, v, ok, vertices);
    }
  }
  return cnt_imposters_subtree += is_imp_v;
}

void reset_used(vector<int>& vertices) {
  for (auto v: vertices) {
    used[v] = 0;
  }
}

void init(int n) {
  for (int i = 0; i < n; ++i) {
    g[i].clear();
    used[i] = 0;
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  init(n);

  string s;
  for (int i = 0; i < m; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    cin >> s;
    bool is_imp = is_imposter(s);
    // cout << "from " << from << ", to: " << to << ", is_imp: " << is_imp << endl;
    g[from].push_back({to, is_imp});
    g[to].push_back({from, is_imp});
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    vector<int> vertices;
    if (!used[i]) {
      bool is_ok_1 = true;
      bool is_ok_2 = true;
      int ans_1 = dfs(i, IMP, -1, is_ok_1, vertices);
      reset_used(vertices);
      vertices.clear();
      // cout << "======\n";
      int ans_2 = dfs(i, CREW, -1, is_ok_2, vertices);
      ans += max(is_ok_1 * ans_1, is_ok_2 * ans_2);

      if (!is_ok_1 && !is_ok_2) {
        ans = -1;
        break;
      }
    }
  }

  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
