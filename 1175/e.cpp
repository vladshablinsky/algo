#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_X = 500005;
const int INF = 1e9;
pair<int, int> f[MAX_X];
int left_last[MAX_X];
bool intersect[MAX_X];
multiset<pair<int, int>> st;

pair<int, int> calc_f(int x, int leftmost) {
  if (leftmost > x) {
    return {-1, -1};
  } else {
    return {f[leftmost].first, f[leftmost].second + 1 - (left_last[leftmost] == leftmost)};
  }
}

int query(int l, int r) {
  if (f[r].first == -1 || f[r].first > l) {
    return -1;
  } else if (f[r].first == l) {
    return f[r].second;
  }
  else {
    int ans = f[r].second - f[l].second + 1 - (intersect[l]);
    if (!ans) {
      ans = 1;
    }
    return ans;
  }
}

int main() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    st.insert({l, r});
  }

  for (int i = 0; i < MAX_X; ++i) {
    left_last[i] = -1;

    while (!st.empty() && st.begin()->second < i) {
      st.erase(st.begin());
    }

    if (!st.empty()) {
      f[i] = {i, 1};
      left_last[i] = st.begin()->first;
      f[i] = calc_f(i, st.begin()->first);
    } else {
      f[i] = {-1, -1};
    }
    if (f[i] != pair<int,int>({-1, -1})) {
      cout << "f[ " << i << " ]" << " = " << f[i].first << ", " << f[i].second << endl;
    }
  }

  int last_left_last = -1;
  for (int i = MAX_X - 1; i >= 0; --i) {
    if (last_left_last != -1 && last_left_last <= i && last_left_last > left_last[i]) {
      cout << "last_left_last: " << last_left_last << ", left_last: " << left_last[i] << endl;
      cout << "intersect " << i << " true \n";
      intersect[i] = true;
    }

    if (last_left_last == -1 || last_left_last == i) {
      last_left_last = left_last[i];
    }
  }

  for (int i = 0; i < m; ++i) {
    int l, r;
    cin >> l >> r;
    cout << query(l, r) << "\n";
  }
  return 0;
}
