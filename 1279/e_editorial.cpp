#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const long long INF = 1e18 + 10;
const int MAXN = 52;

long long cycle[MAXN];
// f[i] -- number of NYPs with i...n on the suffix.
long long f[MAXN];

long long mul(long long x, long long y) {
  if (x >= INF / y) {
    return INF;
  }
  return x * y;
}

long long add(long long x, long long y) {
  return min(INF, x + y);
}

void init_cycle() {
  cycle[0] = 1;
  cycle[1] = 1;
  cycle[2] = 1;
  for (int i = 3; i < MAXN; ++i) {
    cycle[i] = mul(cycle[i - 1], i - 2);
  }
}

void solve() {
  int n;
  long long k;
  cin >> n >> k;

  f[n + 1] = 1;
  f[n] = 1;
  for (int i = n - 1; i >= 1; --i) {
    f[i] = 0;
    for (int front_block_end = i; front_block_end <= n; ++front_block_end) {
      f[i] = add(f[i], mul(cycle[front_block_end - i + 1], f[front_block_end + 1]));
    }
  }

  if (k > f[1]) {
    cout << "-1\n";
    return;
  }

  // Our function generates next after k new year permutations. Thus decrease k.
  --k;

  vector<int> ans(n + 1, -1);
  vector<bool> used(n + 1, false);

  // cout << "Begin\n";

  for (int i = 1; i <= n; ++i) {
    for (int front_block_end = i; front_block_end <= n; ++front_block_end) {
      int len = front_block_end - i + 1; // i ... i + len
      long long cnt_front_block_with_len = mul(cycle[len], f[front_block_end + 1]);
      // cout << "i: " << i << ", len: " << len << ", cnt: " << cnt_front_block_with_len << endl;
      if (cnt_front_block_with_len <= k) {
        k -= cnt_front_block_with_len;
        // cout << "i: " << i << ", skip front_block_end: " << front_block_end << endl;
        continue;
      }
      // cout << "i: " << i << ", front_block_end: " << front_block_end << endl;

      // Max goes first.
      ans[i] = front_block_end;
      used[front_block_end] = true;

      // Now fill the permutation of length len
      // j is the current index we're filling
      for (int j = i + 1; j <= i + len - 1; ++j) {
        for (int value = i; value < front_block_end; ++value) {
          // not awailable or self-loop => skip
          if (used[value] || j == value) {
            continue;
          }

          if (j != i + len - 1) {
            int prev = ans[value];
            while (prev != -1 && prev != j) {
              prev = ans[prev];
            }

            // Found a loop that covers a segment of lenght < len, thus
            // there are several loops on [i...i + len - 1]
            if (prev == j) {
              continue;
            }
          }

          // Originally cycle[x] is the number of permutations such that
          // x is on the first place and then follow the others number
          // 1 ... x - 1.
          //
          // cycle[x] is also equivalent to the number
          // of ways to set directed edges in the graph of x vertices so that
          // graph is connected and has one loop exactly with the condition
          // that one edge is preset and the others can vary.
          //
          // cycle[tail] is equivalent to the number of permutations of
          // numbers excluding those already set in the prefix such that
          // there is only one loop at i ... i + len. Prefix has one loop
          // is ensured above. i ... i + len has one loop and
          // j ... i + len has also one loop resulting to what we need i.e.
          // i ... i + len has one loop.
          int tail = i + len - j;
          long long cnt_with_cur_prefix = mul(f[front_block_end + 1], cycle[tail]);
          // cout << "i: " << i << ", j: " << j << ", tail: " << tail << ", cnt: " << cnt_with_cur_prefix << ", k = " << k << endl;
          if (k >= cnt_with_cur_prefix) {
            // if k == cnt_with_cur_prefix, it means that
            // will just set the least suffix from now on.
            k -= cnt_with_cur_prefix;
            // cout << "i: " << i << ", j: " << j << " skip " << value << " here\n";
            continue;
          }

          // cout << "i: " << i << ", j: " << j << " set " << value << " here\n";

          // j-th found, break and go find j + 1.
          ans[j] = value;
          used[value] = true;
          break;
        }
      }
      // Block found and filled, go find next block.
      i = front_block_end;
      break;
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << " ";
  }
  cout << "\n";
}

int main() {
  init_cycle();
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
