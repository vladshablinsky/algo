#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 2e3 + 5;

long long ans = 1e18;
pair<int, int> points[MAX_N];
bool taken[MAX_N];
int n;
int x_1, x_2, y_1, y_2;

long long sqr(long long x) {
  return x * x;
}

void try_point(int idx) {
  for (int i = 0; i < n; ++i) {
    taken[i] = false;
  }

  long long sqr_r1 = sqr(points[idx].first - x_1) + sqr(points[idx].second - y_1);
  for (int i = 0; i < n; ++i) {
    if (sqr(x_1 - points[i].first) + sqr(y_1  - points[i].second) <= sqr_r1) {
      taken[i] = true;
    }
  }

  long long sqr_r2 = 0;

  for (int i = 0; i < n; ++i) {
    if (!taken[i]) {
      sqr_r2 = max(sqr_r2, sqr(x_2 - points[i].first) + sqr(y_2 - points[i].second));
    }
  }

  ans = min(ans, sqr_r1 + sqr_r2);
}

int main() {
  scanf("%d%d%d%d%d", &n, &x_1, &y_1, &x_2, &y_2);

  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    points[i] = make_pair(x, y);
  }

  points[n] = make_pair(x_1, y_1);
  points[n + 1] = make_pair(x_2, y_2);
  n += 2;

  for (int i = 0; i < n; ++i) {
    try_point(i);
  }
  cout << ans << "\n";
  return 0;
}

