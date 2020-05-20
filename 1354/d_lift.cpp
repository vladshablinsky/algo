#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int BITS = 20;
const int MAXN = (1 << 20) + 5;
int t[MAXN];

void inc(int i, int x) {
  for (; i < MAXN; i = (i | (i + 1))) {
    t[i] += x;
  }
}

int sum(int r) {
  int ans = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) {
    ans += t[r];
  }
  return ans;
}

int lift_to_i(int k) {
  //cout << "lift_to_i: " << k << endl;
  int result = 0;
  // take 2^i start from 0.
  for (int i = BITS - 1; i >= 0; --i) {
    if (t[result + (1 << i) - 1] < k) {
      int from = result + (1 << i) - 1;

      //cout << "try: [" << (from & (from + 1)) << "..." << from << "] = " << t[from] << endl;
      k -= t[result + (1 << i) - 1];
      result += (1 << i);
    }
  }

  //cout << "result: " << result << endl;
  if (result == (1 << BITS) - 1) {
    return 0;
  }
  return result;
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; ++i) {
    int a_i;
    scanf("%d", &a_i);
    inc(a_i, 1);
  }

  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);
    if (k < 0) {
      inc(lift_to_i(-k), -1);
    } else {
      inc(k, 1);
    }
  }
  printf("%d\n", lift_to_i(1));
  return 0;
}

