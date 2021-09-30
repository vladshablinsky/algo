#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int MAXC = 'z' - 'a' + 1;

bool solve() {
  string a, b;
  int n;
  int k;
  vector<int> cnt_a(MAXC, 0);
  vector<int> cnt_b(MAXC, 0);
  scanf("%d%d", &n, &k);
  cin >> a;
  cin >> b;

  for (auto c: a) {
    ++cnt_a[c - 'a'];
  }
  for (auto c: b) {
    ++cnt_b[c - 'a'];
  }

  for (char c = 'a'; c <= 'z'; ++c) {
    int idx = c - 'a';
    if (c != 'z') {
      while (cnt_a[idx] - k >= cnt_b[idx]) {
        cnt_a[idx] -= k;
        cnt_a[idx + 1] += k;
      }
    }

    if (cnt_a[idx] != cnt_b[idx]) {
      return false;
    }
  }
  return true;
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
