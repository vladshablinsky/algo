#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 2005;
long long f[MAXN][MAXN];


int main() {
  int n;
  vector<long long> pref;
  vector<int> neg;

  cin >> n;
  long long cur_sum = 0;
  int a_i;
  for (int i = 0; i < n; ++i) {
    cin >> a_i;
    if (a_i < 0) {
      pref.push_back(cur_sum);
      neg.push_back(a_i);
    } else {
      cur_sum += a_i;
    }
  }

  int ans = 0;
  if (!neg.empty()) {
    f[0][0] = pref[0];
    for (int i = 1; i < neg.size(); ++i) {
      f[0][i] = -1;
    }

    for (int i = 1; i <= neg.size(); ++i) {
      f[i][0] = pref[i];
      for (int j = 1; j <= neg.size(); ++j) {

        f[i][j] = -1;
        if (j > i) {
          continue;
        }

        long long add = 0;
        if (i < pref.size()) {
          add = pref[i] - pref[i - 1];
        }

        if (f[i - 1][j] != -1) {
          f[i][j] = f[i - 1][j] + add;
        }

        if (auto val = f[i - 1][j - 1] + neg[i - 1]; f[i - 1][j - 1] != -1 && val >= 0) {
          f[i][j] = max(f[i][j], val + add);
        }

        if (f[i][j] != -1) {
          ans = max(ans, j);
        }
      }
    }
  }

  cout << n - neg.size() + ans << "\n";
}
