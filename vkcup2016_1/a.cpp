#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 150005;
int n, k, q;
set<int> st;
int t[MAXN + 5];

int main() {
  scanf("%d%d%d", &n, &k, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t[i]);
  }

  for (int i = 0; i < q; ++i) {
    int q_type, id;
    int other;
    scanf("%d%d", &q_type, &id);
    if (q_type == 1) {
      if (!st.empty()) {
        other = *st.begin();
        st.erase(st.begin());
        st.insert(max(other, t[id]));
        if (st.size() < k) {
          st.insert(min(other, t[id]));
        }
      } else {
        st.insert(t[id]);
      }
    } else {
      if (st.find(t[id]) != st.end()) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  }
  return 0;
}

