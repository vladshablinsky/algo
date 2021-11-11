#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }

  return gcd(b, a % b);
}

int solve() {
  vector<int> v;
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    v.push_back(el);
  }

  sort(v.begin(), v.end());
  int cur_gcd = v[1] - v[0];
  for (int i = 2; i < n; ++i) {
    cur_gcd = gcd(cur_gcd, v[i] - v[0]);
  }

  if (cur_gcd == 0) {
    return -1;
  } else {
    return cur_gcd;
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
