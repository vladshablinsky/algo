#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

void solve() {
  int n, w;
  multiset<int> st;
  scanf("%d%d", &n, &w);
  for (int i = 0; i < n; ++i) {
    int val;
    scanf("%d", &val);
    st.insert(-val);
  }

  // how much there still available
  int cur_layer = w;
  int layers = 1;
  while (!st.empty()) {
    auto it = st.lower_bound(-cur_layer);
    if (it != st.end()) {
      cur_layer += *it;
      st.erase(it);
    } else {
      ++layers;
      cur_layer = w;
    }
  }
  printf("%d\n", layers);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
