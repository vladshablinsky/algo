#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool solve() {
  long long a, b;
  int n;
  scanf("%lld%lld%d", &a, &b, &n);

  bool any_skipped = false;
  vector<pair<long long, long long>> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &p[i].first);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &p[i].second);
  }

  std::iter_swap(std::max_element(p.begin(), p.end()), std::prev(p.end()));

  for (auto [a_i, b_i]: p) {
    long long cnt_hits_him = (b_i + a - 1) / a;
    long long cnt_hits_me = (b + a_i - 1) / a_i;

    if (b > 0 && cnt_hits_him <= cnt_hits_me) {
      b -= a_i * cnt_hits_him;
    } else {
      b = 0;
      any_skipped = true;
    }
  }
  return !any_skipped;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
