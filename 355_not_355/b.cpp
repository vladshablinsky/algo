#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

multiset<int> mst;
set<int> st;

int main() {
  int n;
  int ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    mst.insert(t);
  }
  while (!mst.empty()) {
    for (multiset<int>::iterator it = mst.begin(); it != mst.end(); ++it) {
      st.insert(*it);
    }
    ans += st.size() - 1;
    for (set<int>::iterator it = st.begin(); it != st.end(); ++it) {
      mst.erase(mst.find(*it));
    }
    st.clear();
  }

  printf("%d\n", ans);

  return 0;
}
