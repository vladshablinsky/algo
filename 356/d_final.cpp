#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

long long INF = 1e18;

long long cb(long long x) {
  return x * x * x;
}

vector<pair<int, long long> > v;

void solve(long long m, long long x, int cnt) {
  if (m <= 0) {
    v.push_back(make_pair(cnt, x));
    return;
  }

  long long a = (long long)cbrt(m);
  solve(cb(a) - 1 - cb(a - 1), x + cb(a - 1), cnt + 1);
  solve(m - cb(a), x + cb(a), cnt + 1);
}

int main() {
  long long m;
  cin >> m;
  solve(m, 0, 0);
  sort(v.begin(), v.end());
  cout << v.back().first << " " << v.back().second << "\n";
  return 0;
}
