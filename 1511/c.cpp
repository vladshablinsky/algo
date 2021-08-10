#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int MAXC = 55;

int a[MAXN];
int t[MAXN];
bool colors[MAXC];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < q; ++i) {
    scanf("%d", &t[i]);
    colors[t[i]] = true;
  }

  vector<int> ans(q);
  for (int i = 1; i < MAXC; ++i) {
    if (colors[i]) {
      set<int> st;
      int sz = 0;
      while (a[sz] != i) {
        st.insert(a[sz]);
        ++sz;
      }
      int add = sz - st.size();

      bool reset_all = false;
      for (int j = 0; j < q; ++j) {
        if (t[j] !=  i) {
          st.insert(t[j]);
        } else {
          ans[j] = st.size() + 1 + add;
          add = 0;
          st.clear();
        }
      }
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%d ", ans[i]);
  }
  printf("\n");
}
