#include <iostream>
#include <cstdio>
#include <set>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAXN = 100005;

map<pair<int, int>, set<int>> mp;
vector<int> q[MAXN];
int where[MAXN];

void remove_mp(int first, int second, int third) {
  mp[make_pair(first, second)].erase(third);
  mp[make_pair(second, first)].erase(third);
  mp[make_pair(third, second)].erase(first);
  mp[make_pair(second, third)].erase(first);
  mp[make_pair(third, first)].erase(second);
  mp[make_pair(first, third)].erase(second);
}

int find_and_remove(int a, int b) {
  pair<int, int> key = make_pair(a, b);
  int res;
  if (mp.count(key) && !mp[key].empty()) {
    res = *mp[key].begin();
  } else {
    key = make_pair(b, a);
    res = *mp[key].begin();
  }
  remove_mp(a, b, res);
  //cout << "a: " << a << ", b: " << b << ", res: " << res << endl;
  return res;
}

int main() {
  int n;
  scanf("%d", &n);
  multiset<int> st;
  for (int i = 0; i < n - 2; ++i) {
    int cur_el;
    for (int j = 0; j < 3; ++j) {
      scanf("%d", &cur_el);
      q[i].push_back(cur_el);
      where[cur_el] = i;
      st.insert(cur_el);
    }

    mp[make_pair(q[i][0], q[i][1])].insert(q[i][2]);
    mp[make_pair(q[i][0], q[i][2])].insert(q[i][1]);
    mp[make_pair(q[i][1], q[i][2])].insert(q[i][0]);
  }

  int first;
  int second;
  int third;
  for (auto &el: st) {
    if (st.count(el) == 1) {
      first = el;
      for (auto &el_in_q: q[where[el]]) {
        if (st.count(el_in_q) == 2) {
           second = el_in_q;
        } else if (el_in_q != el) {
          third = el_in_q;
        }
      }
      break;
    }
  }

  //cout << first << " " << second << " " << third << endl;

  vector<int> ans;
  ans.push_back(first);
  ans.push_back(second);
  ans.push_back(third);
  remove_mp(first, second, third);


  while (ans.size() != n) {
    int prev = *ans.rbegin();
    int prev_prev = *next(ans.rbegin());
    ans.push_back(find_and_remove(prev_prev, prev));
  }

  for (auto &el: ans) {
    printf("%d ", el);
  }
  printf("\n");
  return 0;
}
