#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

long long j, p, s, k;

void solve(int id) {
  cin >> j >> p >> s >> k;

  long long ans = -1;
  int cs = 0;
  if (min(j * p, min(k, s)) > ans) {
    cs = 1;
    ans = min(j * p, min(k, s));
  }
  if (min(s * p, min(k, j)) > ans) {
    cs = 2;
    ans = min(s * p, min(k, j));
  }
  if (min(j * s, min(k, p)) > ans) {
    cs = 3;
    ans = min(j * s, min(k, p));
  }

  cout << "Case #" << id << ": " << ans << "\n";
  if (cs == 1) {
    for (int ii = 1; ii <= j; ++ii) {
      for (int jj = 1; jj <= p; ++jj) {
        for (int kk = 1; kk <= min(k, s); ++kk) {
          printf("%d %d %d\n", ii, jj, kk);
        }
      }
    }
  } else if (cs == 2) {
    for (int ii = 1; ii <= s; ++ii) {
      for (int jj = 1; jj <= p; ++jj) {
        for (int kk = 1; kk <= min(k, j); ++kk) {
          printf("%d %d %d\n", ii, jj, kk);
        }
      }
    }
  } else {
    for (int ii = 1; ii <= j; ++ii) {
      for (int jj = 1; jj <= s; ++jj) {
        for (int kk = 1; kk <= min(k, p); ++kk) {
          printf("%d %d %d\n", ii, jj, kk);
        }
      }
    }
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
