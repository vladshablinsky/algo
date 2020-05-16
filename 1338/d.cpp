#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 100005;

const int INCLUDE_SELF = 0;
const int EXCLUDE_SELF = 1;

vector<int> g[MAXN];
pair<int, int> f[MAXN][2];
int cnt_sons[MAXN];
int max_f_sons[MAXN];
int max_f_enclose_sons[MAXN];

pair<int, int> find_deepest(int v, int p) {
  pair<int, int> res{v, 0};
  for (auto to: g[v]) {
    if (to != p) {
      auto res_son = find_deepest(to, v);
      if (res_son.second > res.second) {
        res = res_son;
      }
    }
  }
  res.second += 1;
  return res;
}

int ans = 0;
void dfs(int v, int p) {
  //cout << "dfs " << v << " " << p << endl;
  if (g[v].size() == 1 && p != -1) {
    f[v][INCLUDE_SELF] = {1, 1};
    f[v][EXCLUDE_SELF] = {0, 0};
  } else {
    multiset<int> st_not_enclosed_incude_son;
    multiset<int> st_not_enclosed_exclude_son;
    int max_enclosed = 0;
    for (auto to: g[v]) {
      if (to != p) {
        cnt_sons[v]++;

        dfs(to, v);
        st_not_enclosed_incude_son.insert(
            max(f[to][INCLUDE_SELF].second, f[to][EXCLUDE_SELF].second));
        for (auto to_son: g[to]) {
          if (to_son != v) {
            st_not_enclosed_exclude_son.insert(
                max(f[to_son][INCLUDE_SELF].second, f[to_son][EXCLUDE_SELF].second));
          }
        }
      }
    }

    for (auto to: g[v]) {
      if (to != p) {
        // calculate if enclose excluding self:
        //  first try update with value when some child makes enclose.
        int val = max(f[to][INCLUDE_SELF].second, f[to][EXCLUDE_SELF].second);
        st_not_enclosed_incude_son.erase(st_not_enclosed_incude_son.find(val));
        if (st_not_enclosed_incude_son.size()) {
          ans = max(ans, max(f[to][INCLUDE_SELF].first, f[to][EXCLUDE_SELF].first) + cnt_sons[v] - 2 +
              *st_not_enclosed_incude_son.rbegin());
        }

        f[v][EXCLUDE_SELF].first = max(f[v][EXCLUDE_SELF].first,
            max(f[to][INCLUDE_SELF].first, f[to][EXCLUDE_SELF].first) + cnt_sons[v] - 1);
        st_not_enclosed_incude_son.insert(val);

        f[v][INCLUDE_SELF].second = max(f[v][INCLUDE_SELF].second, f[to][EXCLUDE_SELF].second + 1);

        // calculate if enclose including self:
        //  first try update with value when some child makes enclose.
        for (auto to_son: g[to]) {
          if (to_son != v) {
            val = max(f[to_son][INCLUDE_SELF].second, f[to_son][EXCLUDE_SELF].second);
            st_not_enclosed_exclude_son.erase(st_not_enclosed_exclude_son.find(val));
            int other_subtrs = 0;
            if (st_not_enclosed_exclude_son.size()) {
              other_subtrs += *st_not_enclosed_exclude_son.rbegin();
            }
            ans = max(ans,
                max(f[to_son][INCLUDE_SELF].first, f[to_son][EXCLUDE_SELF].first) + other_subtrs);
            f[v][INCLUDE_SELF].first = max(f[v][INCLUDE_SELF].first,
                max(f[to_son][INCLUDE_SELF].first, f[to_son][EXCLUDE_SELF].first)+ 1);
            st_not_enclosed_exclude_son.insert(val);
          }
        }
      }
    }

    f[v][EXCLUDE_SELF].second = *st_not_enclosed_incude_son.rbegin() + cnt_sons[v] - 1;
    f[v][INCLUDE_SELF].first = max(f[v][INCLUDE_SELF].first, f[v][INCLUDE_SELF].second);
  }

  //cout << v << ": f_v_include: (" << f[v][INCLUDE_SELF].first << ", " << f[v][INCLUDE_SELF].second<< "), f_v_exclude: (" << f[v][EXCLUDE_SELF].first << "," << f[v][EXCLUDE_SELF].second << ")\n";

  ans = max(ans, f[v][INCLUDE_SELF].first);
  ans = max(ans, f[v][INCLUDE_SELF].second);
  ans = max(ans, f[v][EXCLUDE_SELF].first);
  ans = max(ans, f[v][EXCLUDE_SELF].second);
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  dfs(1, -1);
  cout << ans << "\n";
  return 0;
}
