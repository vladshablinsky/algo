#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int INF = 1e9 + 5;

multiset<int> st;
vector<pair<string, int> > ans;

int cur_min() {
  int cur_min = -INF;
  if (st.begin() != st.end()) {
    cur_min = *st.begin();
  }
  return cur_min;
}

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    string s;
    int t;
    cin >> s;
    scanf("%d", &t);

    if (s == "getMin") {
      while (!st.empty() && cur_min() < t) {
        ans.push_back(make_pair("removeMin", 0));
        st.erase(st.begin());
      }
      if (st.empty() || cur_min() > t) {
        ans.push_back(make_pair("insert", t));
        st.insert(t);
      }
      ans.push_back(make_pair("getMin", t));
    } else if (s == "insert") {
      st.insert(t);
      ans.push_back(make_pair("insert", t));
    } else {
      if (st.empty()) {
        ans.push_back(make_pair("insert", 0));
      } else {
        st.erase(st.begin());
      }
      ans.push_back(make_pair("removeMin", 0));
    }
  }
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); ++i) {
    if (ans[i].first == "removeMin") {
      printf("removeMin\n");
    } else {
      cout << ans[i].first << " " << ans[i].second << "\n";
    }
  }
  return 0;
}
