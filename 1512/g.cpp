#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN= 10000005;
int lp[MAXN];
int d[MAXN];
int ans[MAXN];
vector<int> p;

void prepare_sieve() {
  for (int i = 2; i < MAXN; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      p.push_back(i);
    }

    for (int j = 0; j < (int)p.size() && p[j] <= lp[i] && p[j] * 1ll * i < MAXN; ++j) {
      lp[i * p[j]] = p[j];
    }
  }
}

void prepare_d_and_ans() {
  for (int i = 1; i < MAXN; ++i) {
    long long result_d = 1;
    int cur_i = i;

    while (cur_i != 1) {
      int cur_div = lp[cur_i];
      int cur_div_sum = cur_div;
      while (lp[cur_i] == lp[cur_i / lp[cur_i]]) {
        cur_div *= lp[cur_i];
        cur_div_sum += cur_div;
        cur_i /= lp[cur_i];
      }

      result_d *= (cur_div_sum + 1);
      cur_i /= lp[cur_i];
      if (result_d >= MAXN) {
        cur_i = 1;
        result_d = MAXN;
      }
    }

    d[i] = result_d;
    ans[i] = MAXN; // set to inf.
  }

  for (int i = 1; i < MAXN; ++i) {
    if (d[i] < MAXN) {
      ans[d[i]] = min(ans[d[i]], i);
    }
  }
}

int main() {
  prepare_sieve();
  prepare_d_and_ans();

  int t;
  scanf("%d", &t);
  while (t--) {
    int c;
    scanf("%d", &c);
    if (ans[c] == MAXN) {
      printf("-1\n");
    } else {
      printf("%d\n", ans[c]);
    }
  }
}
