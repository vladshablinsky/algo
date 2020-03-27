#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <ctime>
#include <chrono>


using namespace std;

const int MAXN = 200005;
const int MOD = 998244353;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int a[MAXN];
int segs[MAXN];

int binpow(int a, int pow) {
  if (pow == 0) {
    return 1;
  } else {
    if (pow % 2) {
      return (a * 1ll * binpow(a, pow - 1)) % MOD;
    } else {
      int res = binpow(a, pow / 2);
      return (res * 1ll * res) % MOD;
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  unordered_map<int, pair<int, int>, custom_hash> intervals;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    if (!intervals.count(a[i])) {
      intervals[a[i]] = {i, i};
    } else {
      auto &cur_interval = intervals[a[i]];
      segs[cur_interval.second]++;
      segs[i]--;
      cur_interval.second = i;
    }
  }

  //for (auto el: open) {
  //  cout << "for " << el.first << " should be same: " << el.second << " " << close[el.first] << endl;
  //}

  int cur_balance = segs[0];
  int idx = 1;
  while (cur_balance && idx < n) {
    cur_balance += segs[idx++];
  }
  int cnt_no_intersect_segs = 0;
  for (; idx < n; ++idx) {
    cur_balance += segs[idx];
    if (cur_balance == 0) {
      ++cnt_no_intersect_segs;
    }
  }

  printf("%d\n", binpow(2, cnt_no_intersect_segs));
  return 0;
}
