#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

const int MAXN = 1000006;
long double EPS = 1e-6;

struct Rect {
  int x;
  int y;
  long long a;
  Rect() {}
  Rect(int x, int y, int a): x(x), y(y), a(a) {};
};

bool cmp(const Rect &a, const Rect &b) {
  return a.x < b.x;
}

Rect v[MAXN];

struct Line {
  long long m, c;
  Line() {};
  Line(long long m, long long c): m(m), c(c) {}
  long long fun(long long x) {
    return m * x + c;
  }
  long double intersection_x(const Line &other) const {
    return ((long double)other.c - c) / (m - other.m);
  }
};

struct CHT {
  deque<Line> dq;
  void add_min_slope_line(const Line &l) {
    while (dq.size() >= 2 &&
        l.intersection_x(*dq.begin()) + EPS > dq.begin()->intersection_x(*next(dq.begin()))) {
      dq.pop_front();
    }
    dq.push_front(l);
  }

  long long query_next_deq(long long x) {
    while (dq.size() >= 2 && dq.rbegin()->fun(x) < next(dq.rbegin())->fun(x)) {
      dq.pop_back();
    }
    return dq.rbegin()->fun(x);
  }
};

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d%I64d", &v[i].x, &v[i].y, &v[i].a);
  }
  sort(v, v + n, cmp);
  long long ans = 0;

  CHT cht;
  cht.add_min_slope_line(Line(0, 0));
  for (int i = 0; i < n; ++i) {
    long long f_i = -v[i].a + v[i].x * 1ll * v[i].y + cht.query_next_deq(v[i].y);
    cht.add_min_slope_line(Line(-v[i].x, f_i));
    ans = max(ans, f_i);
  }

  cout << ans << "\n";
  return 0;
}
