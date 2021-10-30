#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXP = 19;
long long pows[MAXP];

void init_pows() {
  pows[0] = 1ll;
  for (int i = 1; i < MAXP; ++i) {
    pows[i] = pows[i - 1] * 10;
  }
}

long long solve() {
  long long a[MAXP];
  for (int i = 0; i < MAXP; ++i) {
    a[i] = 0;
  }

  int n;
  long long k;
  scanf("%d%lld", &n, &k);
  for (int i = 0; i < n; ++i) {
    int pow;
    scanf("%d", &pow);
    a[pow] = 1;
  }

  for (int i = 1; i < MAXP; ++i) {
    if (a[i] != 1) {
      a[i] = a[i - 1] * 10;
    }
  }

  long long cur_cnt = 0;
  long long number = 0;
  int pow = 0;
  while (cur_cnt <= k) {
    cur_cnt += a[pow] * 9;
    number += pows[pow] * 9;
    ++pow;
  }

  --pow;
  while (cur_cnt > k + 1) {
    // cout << pow << endl;
    while (number > pows[pow] && cur_cnt - a[pow] >= k + 1) {
      cur_cnt -= a[pow];
      number -= pows[pow];
      // cout << "number: " << number << " " << cur_cnt << endl;
    }
    --pow;
  }

  return number;
}

int main() {
  init_pows();
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%lld\n", solve());
  }
}
