#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
long long t[4 * MAXN];

void update(int v, int tl, int tr, int pos, int val) {
  if (tl == tr) {
    t[v] = val;
  } else {
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
      update(v * 2, tl, tm, pos, val);
    } else {
      update(v * 2 + 1, tm + 1, tr, pos, val);
    }
    t[v] = t[v * 2] + t[v * 2 + 1];
  }
}

long long sum(int v, int tl, int tr, int l, int r) {
  if (tl > tr || l > r) {
    return 0;
  }
  if (tl == tr) {
    return t[v];
  } else {
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(tm, r)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
  }
}

int main() {
  int n;
  vector<long long> pref;
  vector<pair<int, int>> neg;

  cin >> n;
  long long cur_sum = 0;
  int a_i;
  for (int i = 0; i < n; ++i) {
    cin >> a_i;
    if (a_i < 0) {
      pref.push_back(cur_sum);
      neg.emplace_back(-a_i, neg.size());
    } else {
      cur_sum += a_i;
    }
  }

  sort(neg.begin(), neg.end());
  int cnt = 0;
  for (int sz = neg.size(), i = 0; i < sz; ++i) {
    auto [el, j] = neg[i];
    long long pref_j = pref[j];
    long long substract_sum = sum(1, 0, sz - 1, 0, j);
    printf("el:%d, j:%d, pref_j:%lld, substr:%lld\n", el, j, pref_j, substract_sum);

    if (pref_j - substract_sum >= el) {
      cout << "take!\n";
      ++cnt;
      update(1, 0, sz - 1, j, el);
    }
  }

  cout << n - neg.size() + cnt << "\n";

  return 0;
}
