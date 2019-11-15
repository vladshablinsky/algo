#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

long long gcd(long long a, long long b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a % b);
  }
}

int main() {
  int n, m;
  vector<long long> v;
  cin >> n >> m;
  v.resize(n);

  int ans_idx = -1;
  long long cur_gcd = -1;
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());

  for (int i = 0; i + 1 < n; ++i) {
    if (v[i] == v[i + 1]) {
      continue;
    }
    if (cur_gcd == -1) {
      cur_gcd = v[i + 1] - v[i];
    } else {
      cur_gcd = gcd(cur_gcd, v[i + 1] - v[i]);
    }
  }

  for (int i = 0; i < m; ++i) {
    long long cur_p;
    cin >> cur_p;
    if (cur_gcd != -1 && cur_gcd % cur_p == 0) {
      ans_idx = i + 1;
    }
  }

  if (cur_gcd == -1) {
    cout << "YES\n" << v[0] << " 1\n";
  } else {
    if (ans_idx == -1) {
      cout << "NO\n";
    } else {
      cout << "YES\n" << v[0] << " " << ans_idx << "\n";
    }
  }
  return 0;
}
