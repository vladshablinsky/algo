#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

constexpr int kMaxN = 100005;
bool is_square[kMaxN];
int closest_geq_sqr[kMaxN];

void init_is_squares() {
  for (int i = 0; i * i <= kMaxN; ++i) {
    is_square[i * i] = true;
  }

  int n = 0;
  for (int i = 0; i < kMaxN; ++i) {
    while (n * n < i) {
      ++n;
    }
    closest_geq_sqr[i] = n * n;
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> res(n);

  for (int i = n - 1; i >= 0;) {
    int sqr = closest_geq_sqr[i];
    //cout << "i: " << i << ", sqr: " << sqr << endl;
    int j = sqr - i;
    res[j++] = i;
    for (; j <= i; ++j) {
      res[j] = res[j - 1] - 1;
    }
    i = res[j - 1] - 1;
  }

  for (auto el: res) {
    printf("%d ", el);
  }
  printf("\n");
}

int main() {
  init_is_squares();
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
