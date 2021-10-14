#include <iostream>
#include <vector>

using namespace std;

const int INF = 1000000007;

bool check(int a, int b, int c) {
  return (a < b && b > c) || (a > b && b < c);
}

int calc_range(const vector<int>& v, int mid, int n) {
  int result = 0;
  for (int i = max(0, mid - 2) + 1; i <= min(mid + 2, n - 1) - 1; ++i) {
    result += check(v[i - 1], v[i], v[i + 1]);
  }
  return result;
}

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> v;
  for (int i = 0; i < n; ++i) {
    v.push_back({});
    scanf("%d", &v.back());
  }

  int regular_sum = 0;
  int max_reduce_number = 0;

  for (int i = 0; i < n; ++i) {
    if (i && i + 1 < n) {
      regular_sum += check(v[i - 1], v[i], v[i + 1]);
    }

    int regular = calc_range(v, i, n);

    // calc reduced...
    int prev = v[i];
    v[i] = v[i - 1];
    int reduced = calc_range(v, i, n);
    if (i + 1 < n) {
      v[i] = v[i + 1];
      reduced = min(reduced, calc_range(v, i, n));
    }
    v[i] = prev;

    max_reduce_number = max(max_reduce_number, regular - reduced);
  }

  printf("%d\n", regular_sum - max_reduce_number);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
