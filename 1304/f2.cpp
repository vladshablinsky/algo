#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXM = 20005;
const int MAXN = 55;
const long long INF = 1000000000 * 1ll * 1000000000;

int pref_sums[MAXN][MAXM];
long long prev_f[MAXM];
long long cur_f[MAXM];

struct tnode {
  long long value;
  long long push_value;
  int length;
  tnode(): value(0), push_value(0) {};
};

tnode t[4 * MAXM];

void push(int v) {
  if (t[v].push_value) {
    t[v].value += t[v].push_value;
    //cout << "push " << v << endl;

    if (t[v].length > 1) {
      t[v * 2].push_value += t[v].push_value;
      t[v * 2 + 1].push_value += t[v].push_value;
    }
    t[v].push_value = 0;
  }
}

// supports only add positive operations
void add_on_segment(int v, int tl, int tr, int l, int r, int val) {
  push(v);
  if (l > r) {
    return;
  }
  //cout << "add_on_segment:" << v << " (" << tl << "..." << tr << ") - (" << l << "," << r << "), val:" << val << ", cur: " << t[v].value << endl;

  if (l == tl && r == tr) {
    t[v].push_value += val;
    push(v);
    //cout << "full: " << t[v].value << endl;
  } else {

    int tm = (tl + tr) / 2;
    add_on_segment(v * 2, tl, tm, l, min(r, tm), val);
    add_on_segment(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r, val);
    t[v].value = max(t[v * 2].value, t[v * 2 + 1].value);
    //cout << "result " << v << " -- max(" << t[v * 2].value << ","<<t[v*2+1].value << ")" << endl;
  }
}

long long get_max(int v, int tl, int tr, int l, int r) {
  if (l > r) {
    return -INF;
  }

  push(v);
  if (tl == l && tr == r) {
    return t[v].value;
  } else {
    int tm = (tl + tr) / 2;
    return max(get_max(v * 2, tl, tm, l, min(tm, r)),
        get_max(v * 2 + 1, tm + 1, tr, max(tm + 1, l), r));
  }
}

long long get_segment_sum(int level, int l, int r) {
  return pref_sums[level][r] - pref_sums[level][l - 1];
}

void init_t(int v, int tl, int tr, int k, int level) {
  if (tl == tr) {
    t[v].value = prev_f[tl] - get_segment_sum(level - 1, tl, tl + k - 1);
    //cout << "init " << tl << " with " << t[v].value << "=" << prev_f[tl] <<"-"<< get_segment_sum(level - 1, tl, tl + k - 1)<< endl;
    t[v].push_value = 0;
    t[v].length = 1;
  } else {
    int tm = (tl + tr) / 2;
    init_t(v * 2, tl, tm, k, level);
    init_t(v * 2 + 1, tm + 1, tr, k, level);
    t[v].value = max(t[v * 2].value, t[v * 2 + 1].value);
    t[v].push_value = 0;
    t[v].length = t[v * 2].length + t[v * 2 + 1].length;
  }
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int el;
      scanf("%d", &el);
      pref_sums[i][j] = pref_sums[i][j - 1] + el;
    }
  }

  long long ans = 0;
  // should fill first two layers manually
  for (int j = 1; j + k - 1 <= m; ++j) {
    prev_f[j] = get_segment_sum(1, j, j + k - 1);
    if (n >= 2) {
      prev_f[j] += get_segment_sum(2, j, j + k - 1);
    }
    ans = max(ans, prev_f[j]);
  }

  for (int i = 3; i <= n + 1; ++i) {
    //cout << "layer: " << i << endl;
    // left to right
    init_t(1, 1, m - k + 1, k, i);
    for (int j = 1; j + k - 1 <= m; ++j) {
      int cnt_in_first = get_segment_sum(i - 1, j, j);
      //cout << "max(" << 1 << ", " << j << ") = " << get_max(1, 1, m - k + 1, 1, j)  << endl;

      cur_f[j] = get_max(1, 1, m - k + 1, 1, j) + get_segment_sum(i - 1, j, j + k - 1) +
        get_segment_sum(i, j, j + k - 1);
      //cout << "[" << j << "..." << j + k - 1 << "] -- " << get_max(1, 1, m - k + 1, 1, j) << "+"<< get_segment_sum(i - 1, j, j + k - 1) << "+"<< get_segment_sum(i, j, j + k - 1) << ", add " << cnt_in_first << " on segment [" << j << "..." << max(1, j - k + 1) << "]\n";
      add_on_segment(1, 1, m - k + 1, max(1, j - k + 1), j, cnt_in_first);
      //int x;
      //cin >> x;
    }

    // right to left
    init_t(1, 1, m - k + 1, k, i);
    for (int j = m - k + 1; j >= 1; --j) {
      int cnt_in_last = get_segment_sum(i - 1, j + k - 1, j + k - 1);
      long long cur_max_rl = get_max(1, 1, m - k + 1, j, m - k + 1) +
        get_segment_sum(i - 1, j, j + k - 1) + get_segment_sum(i, j, j + k - 1);
      //cout << "max(" << j << ", " << m - k + 1<< ") = " << get_max(1, 1, m - k + 1, j, m - k + 1)  << endl;
      cur_f[j] = max(cur_f[j], cur_max_rl);
      //cout << "<-[" << j << "..." << j + k - 1 << "] -- " << get_max(1, 1, m - k + 1, j, m - k + 1) << "+"<< get_segment_sum(i - 1, j, j + k - 1) << "+"<< get_segment_sum(i, j, j + k - 1) << ", add " << cnt_in_last << " on segment [" << j << "..." << min(m - k + 1, j + k - 1) << "]\n";
      add_on_segment(1, 1, m - k + 1, j, min(j + k - 1, m - k + 1), cnt_in_last);
      ans = max(ans, cur_f[j]);
    }
    //int x;
    //cin >> x;
    swap(cur_f, prev_f);
  }

  cout << ans << "\n";
  return 0;
}
