#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main() {
  int n, m, d;
  vector<pair<int, int>> v;
  vector<int> ans;
  set<pair<int, int>> st;
  scanf("%d %d %d", &n, &m, &d);
  ans.resize(n);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    v.push_back(make_pair(t, i));
  }
  sort(v.begin(), v.end());

  st.insert(make_pair(v[0].first + d + 1, 1));
  ans[v[0].second] = 1;

  for (int i = 1; i < v.size(); ++i) {
    int minute = v[i].first;
    int id = v[i].second;

    auto it = st.begin();
    int cur_min_available_minute = it->first;
    int day = it->second;

    if (cur_min_available_minute <= m && minute >= cur_min_available_minute) {
      st.erase(it);
      st.insert(make_pair(minute + d + 1, day));
      ans[id] = day;
    } else {
      st.insert(make_pair(minute + d + 1, st.size() + 1));
      ans[id] = st.size();
    }
  }

  printf("%d\n", (int)st.size());
  for (int i = 0; i < n; ++i) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  return 0;
}
