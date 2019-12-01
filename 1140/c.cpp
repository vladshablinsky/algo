#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int MAXN = 300005;

pair<int, int> b_t[MAXN];
long long sum_of_max_to_r[MAXN];


int main() {
  int n, k;
  long long ans = 0;
  long long cur_sum = 0;

  scanf("%d%d", &n, &k);

  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &b_t[i].second, &b_t[i].first);
  }

  sort(b_t, b_t + n);
  multiset<int> st;
  for (int i = n - 1; i >= 0; --i) {
    if (st.size() == k) {
      cur_sum -= *st.begin();
      st.erase(st.begin());
    }

    sum_of_max_to_r[i] = cur_sum;
    cur_sum += b_t[i].second;
    st.insert(b_t[i].second);
  }


  for (int i = 0; i < n; ++i) {
    ans = max(ans, (sum_of_max_to_r[i] + b_t[i].second) * b_t[i].first);
  }

  cout << ans << "\n";
  return 0;
}
