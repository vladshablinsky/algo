#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 10;
const int MAX_T = 2 * 1e5 + 10;
const int MAX_S_T = 4 * MAX_T;
int t_in[MAX_T];
int t_out[MAX_T];
vector<int> g[MAX_N];
bool used[MAX_N];
int t[MAX_S_T];
int a[MAX_T];

void update(int v, int tl, int tr, int l, int r, int add) {
  if (l > r)
    return;
  if (l == tl && tr == r)
    t[v] += add;
  else {
    int tm = (tl + tr) / 2;
    update (v * 2, tl, tm, l, min(r, tm), add);
    update (v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, add);
  }
}

int get(int v, int tl, int tr, int pos) {
  if (tl == tr)
    return t[v];
  int tm = (tl + tr) / 2;
  if (pos <= tm)
    return t[v] + get (v * 2, tl, tm, pos);
  else
    return t[v] + get (v * 2 + 1, tm + 1, tr, pos);
}

int timer = 0;
void dfs (int v) {
  ++timer;
  used[v] = true;
  t_in[v] = timer;
  for (int i = 0; i < g[v].size(); ++i) {
    int to = g[v][i];
    if (!used[to]) {
      dfs(to);
    }
  }
  ++timer;
  t_out[v] = timer;
}

int main() {
  int n;
  int t_cnt;
  scanf("%d", &n);
  a[0] = 0;
  for (int i = 1; i < n; ++i) {
    int to;
    scanf("%d", &to);
    --to;
    a[i] = to;
    g[to].push_back(i);
    g[i].push_back(to);
  }
  dfs(0);
  //for (int i = 0; i < n; ++i) {
    //cout << t_in[i] << " ";
  //}
  //cout << endl;

  for (int i = 0; i < n; ++i) {
    update(1, 0, MAX_T, t_in[i], t_out[i], 1);
    cout << i << " add " << t_in[i] << " " << t_out[i] << endl;
  }
  scanf("%d", &t_cnt);
  for (int i = 0; i < t_cnt; ++i) {
    int q_type;
    scanf("%d", &q_type);
    if (q_type == 1) {
      int v1, v2;
      scanf("%d%d", &v1, &v2);
      --v1;
      --v2;
      //cout << get(1, 0, MAX_T, t_in[v1]) << " and " << get(1, 0, MAX_T, t_in[v2]) << endl;
      int to_root_v1 = get(1, 0, MAX_T, t_in[v1]) - 1;
      int to_root_v2  = get(1, 0, MAX_T, t_in[v2]) - 1;
      if (t_out[v1] > t_out[v2] && t_in[v1] < t_in[v2]) {
        printf("%d\n", to_root_v2 - to_root_v1);
      } else if (t_out[v2] > t_out[v1] && t_in[v2] < t_in[v1]) {
        printf("%d\n", to_root_v1 - to_root_v2);
      } else if (t_out[v1] < t_in[v2] || t_out[v2] < t_in[v1]) {
        cout << a[v1] << " " << a[v2] << endl;
        int ans = to_root_v1 + to_root_v1 -  2 * min(get(1, 0, MAX_T, t_in[a[v1]]) - 1, get(1, 0, MAX_T, t_in[a[v2]]) - 1);
        printf("%d\n", ans);
      } else {
        printf("%d\n", to_root_v1 + to_root_v2);
      }
    } else {
      int v_d;
      scanf("%d", &v_d);
      --v_d;
      update(1, 0, MAX_T, t_in[v_d], t_out[v_d], -1);
    }
  }
  return 0;
}
