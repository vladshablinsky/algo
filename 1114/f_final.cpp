//#pragma comment(linker, "/STACK:36777216")
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

const int MAXQ = 200005;
const int MAXN = 400002;
const int MAXPOW = 100000;
const int MAXP = 302;
const int MOD = 1e9 + 7;

vector<int> fact[MAXP];
vector<int> pows[MAXP];  // only prime pows here exist
vector<long long> els[MAXP];

int a[MAXN];
int n;


int binpow(int a, long long b) {
  if (b == 0) {
    return 1;
  } else {
    if (b & 1) {
      return (a * 1ll * binpow(a, b - 1)) % MOD;
    } else {
      long long res = binpow(a, b / 2);
      return (res * res) % MOD;
    }
  }
}

void init_aux() {
  // factorize them all
  int k = 0;
  for (int i = 2; i <= MAXP; ++i) {
    int cur_n = i;
    for (int j = 2; j * j <= cur_n; ++j) {
      while (cur_n % j == 0) {
        fact[i].push_back(j);
        cur_n /= j;
      }
    }
    if (cur_n != 1) {
      fact[i].push_back(cur_n);
    }
    if (cur_n == i) {
      ++k;
      bit[i].resize(n, 0);
    }
  }
  cout << k << endl;
}


// add value to each 0...r
void add_on_segment(int factor, int l, int r, int value) {
  //cout << "add on segment: " << factor<< " for " << "(" << l << "," << r << ") with " << value << endl;

  for (int i = r; i >= l; i = (i & (i + 1)) - 1) {
    for (int j = i; j < n; j = (j | (j + 1))) {
      int tr = j;
      int tl = j & (j + 1);
      int cnt = min(r, tr) - max(tl, l) + 1;
      bit[factor][j] += cnt * value;
    }
  }
}

long long get_ans(int factor, int r) {
  long long ans = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) {
    ans += bit[factor][r];
  }
  return ans;
}

long long get_ans(int factor, int l, int r) {
  return get_ans(factor, r) - get_ans(factor, l - 1);
}

int main() {
  int q;
  scanf("%d%d", &n, &q);
  init_aux();
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);

    // initialize BITs
    for (auto factor: fact[a[i]]) {
      add_on_segment(factor, i, i, 1);
    }
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    string s;
    cin >> s;
    if (s == "MULTIPLY") {
      int x;
      scanf("%d%d%d", &l, &r, &x);
      for (auto factor: fact[x]) {
        add_on_segment(factor, l - 1, r - 1, 1);
      }
    } else if (s == "CNT"){
      int x;
      scanf("%d%d%d", &l, &r, &x);
      cout << get_ans(x, l - 1, r - 1) << endl;
    }
    else {
      scanf("%d%d", &l, &r);
      long long ans = 1;
      for (int factor = 2; factor < MAXP; ++factor) {
        if (!bit[factor].empty()) {
          long long pow = get_ans(factor, l - 1, r - 1);
          if (pow) {
            ans = (ans * binpow(factor, pow - 1)) % MOD;
            ans = (ans * (factor - 1)) % MOD;
          }
        }
      }
      printf("%d\n", (int)ans);
    }
  }
  return 0;
}
