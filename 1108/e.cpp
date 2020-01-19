#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 4;
const int MAXM = 302;
const int INF = 1e9;
const int OPEN = 0;
const int CLOSE = 1;

struct node {
  int length;
  int add;
  int mn;
  int mx;
  node(): length(0), add(0), mn(0), mx(0) {}
} t[4*MAXN];

vector<int> a;
pair<int, int> segments[MAXM];
vector<int> events[MAXN];  // events[i][j] is number of segment and whether it closes or opens

void push(int v) {
  if (t[v].add) {
    t[v].mn += t[v].add;
    t[v].mx += t[v].add;
    if (t[v].length != 1) {
      t[v * 2].add += t[v].add;
      t[v * 2 + 1].add += t[v].add;
    }
    t[v].add = 0;
  }
}

void build(int v, int tl, int tr) {
  t[v].add = 0;
  if (tl == tr) {
    t[v].mn = t[v].mx = a[tl];
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    t[v].length = t[v * 2].length + t[v * 2 + 1].length;
    t[v].mn = min(t[v * 2].mn, t[v * 2 + 1].mn);
    t[v].mx = max(t[v * 2].mx, t[v * 2 + 1].mx);
  }
}

void query_add(int v, int tl, int tr, int l, int r, int add) {
  if (l > r) {
    return;
  }

  if (tl == l && tr == r) {
    t[v].add += add;
  } else {
    push(v);
    int tm = (tl + tr) / 2;
    query_add(v * 2, tl, tm, l, min(tm, r), add);
    query_add(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, add);
    t[v].mn = min(t[v * 2].mn + t[v * 2].add, t[v * 2 + 1].mn + t[v * 2 + 1].add);
    t[v].mx = max(t[v * 2].mx + t[v * 2].add, t[v * 2 + 1].mx + t[v * 2 + 1].add);
    //printf("after query add (%d,(%d,%d), (%d,%d), %d), res is (%d, %d), add: %d\n",
        //v,tl,tr,l,r,add,t[v].mn, t[v].mx, t[v].add);
  }
}

pair<int, int> query_ans(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return {INF, -INF};
  } else {
    if (tl == l && tr == r) {
      //printf("ans(%d, (%d,%d) is (%d, %d)", v, l, r, t[v].mn + t[v].add, t[v].mx + t[v].add);
      return {t[v].mn + t[v].add, t[v].mx + t[v].add};
    } else {
      push(v);
      int tm = (tl + tr) / 2;
      auto q_l = query_ans(v * 2, tl, tm, l, min(tm, r));
      auto q_r = query_ans(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r);
      return {min(q_l.first, q_r.first), max(q_l.second, q_r.second)};
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    a.push_back(t);
  }

  build(1, 0, n - 1);
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l; --r;
    events[l].push_back(r);
    events[r + 1].push_back(l);
    segments[i] = {l, r};
    query_add(1, 0, n - 1, l, r, -1);
  }


  int ans = *max_element(a.begin(), a.end()) - *min_element(a.begin(), a.end());
  //cout << "ANS = " << ans << endl;
  int idx = -1;
  for (int i = 0; i < n; ++i) {
    //cout << "i: " << i << endl;
    for (auto ev: events[i]) {
      if (ev >= i) {
        //cout << "rollback " << i << "..." << ev << endl;
        query_add(1, 0, n - 1, i, ev, 1);
      } else {
        //cout << "add " << ev << "..." << i - 1 << endl;
        query_add(1, 0, n - 1, ev, i - 1, -1);
      }
    }
    auto res = query_ans(1, 0, n - 1, 0, n - 1);
    if (res.second - res.first > ans) {
      ans = res.second - res.first;
      idx = i;
    }
  }

  // Getting the answer.
  printf("%d\n", ans);
  vector<int> ans_segs;
  if (idx != -1) {
    for (int i = 0; i < m; ++i) {
      if (idx < segments[i].first || idx > segments[i].second) {
        ans_segs.push_back(i);
      }
    }
  }
  printf("%d\n", (int)ans_segs.size());
  if (ans_segs.size()) {
    for (int id: ans_segs) {
      printf("%d ", id + 1);
    }
    printf("\n");
  }
  return 0;
}
