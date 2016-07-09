#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

const int MAX_N = 1e5 + 5;

set<int> st_max_less;
set<int> st_min_more;
map<int, int> mp;
int a[MAX_N];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    mp[a[i]] = i;
  }

  st_max_less.insert(-a[0]);
  st_min_more.insert(a[0]);
  for (int i = 1; i < n; ++i) {
    auto it_max_less = st_max_less.lower_bound(-a[i]);
    auto it_min_more = st_min_more.lower_bound(a[i]);

    if (it_max_less == st_max_less.end()) {
      printf("%d ", *it_min_more);
    } else if (it_min_more == st_min_more.end()) {
      printf("%d ", -*it_max_less);
    } else {
      int max_less = -*it_max_less;
      int min_more = *it_min_more;
      if (mp[max_less] > mp[min_more]) {
        printf("%d ", -*it_max_less);
      } else {
        printf("%d ", *it_min_more);
      }
    }
    st_max_less.insert(-a[i]);
    st_min_more.insert(a[i]);
  }
  printf("\n");
  return 0;
}
