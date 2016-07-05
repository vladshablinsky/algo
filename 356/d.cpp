#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1e5 + 5;

int cnt[MAX_N];

long long cube(long long x) {
  return x * x * x;
}

int main() {
  long long cur_volume = 0;
  for (int i = 1; i < MAX_N; ++i) {
    cnt[i] = (cube(i + 1) - cur_volume - 1) / cube(i);
    if (i < 12) {
      cout << cur_volume << " - " << cnt[i] << " cube is " << cube(i) << endl;
    }
    cur_volume += cnt[i] * cube(i);
  }


  long long m;
  cin >> m;

  int cnt_blocks = 0;
  long long X = 0;

  for (int i = 1; i < MAX_N; ++i) {
    long long vol = cube(i);
    int prev = 0;
    if (!cnt[i]) {
      continue;
    }
    for (int j = 0; j < cnt[i]; ++j) {
      X += vol;
      ++cnt_blocks;
      if (X > m) {
        break;
      }
    }
    if (X > m) {
      long long ans = X - vol;
      X -= vol;
      X -= cube(prev);
      for (int j = prev;; ++j) {
        if (!cnt[j]) {
          continue;
        }
        if (X + cube(j) <= m) {
          ans = X + cube(j);
        } else {
          break;
        }
      }
      cout << cnt_blocks - 1 << " " << ans << "\n";
      return 0;
    } else {
      prev = i;
    }
  }
  return 0;
}
