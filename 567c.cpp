#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 200000;

int n, k;
map<int, vector<char> > mp;

long long f[2][4][34];

void init_f() {
  for (int j = 0; j < 4; ++j) {
    for (int l = 0; l < 34; ++l) {
      f[0][j][l] = 0;
    }
  }
  for (int l = 0; l < 34; ++l) {
    f[0][0][l] = 1;
  }
}

long long calc_for(int num, vector<char> &v) {
  // cout << "in calc_for " << num << endl;
  // for (int i = 0; i < v.size(); ++i) {
  //   cout << (int)v[i] << " ";
  // }
  // cout << endl;

  if (num == 0 || k == 1) {
    long long s = v.size();
    return s * (s - 1) * (s - 2) / 6;
  }

  init_f();
  for (int i = 0; i < v.size(); ++i) {
    /* len is j */
    for (int j = 1; j < 4; ++j) {
      /* ends with power l - 1 */
      for (int l = 1; l < 34; ++l) {
        f[1][j][l] = f[0][j][l];
        if (v[i] == l) {
          f[1][j][l] += f[0][j - 1][l - 1];
        }
      }
    }
    // cout << "i = " << i + 1 << endl;
    for (int j = 1; j < 4; ++j) {
      for (int l = 1; l < 34; ++l) {
        f[0][j][l] = f[1][j][l];
        // cout << f[1][j][l] << " ";
      }
      // cout << endl;
    }
  }

  long long ans = 0;
  for (int l = 1; l < 34; ++l) {
      ans += f[0][3][l];
  }
  // cout << "ANS IS " << ans << endl;
  return ans;
}

int main()
{
  long long ans = 0;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    int tmp;
    char power = 0;
    scanf("%d", &tmp);
    if (k == 1 || tmp == 0) {
      mp[tmp].push_back(-1);
    } else {
      while ((tmp % k) == 0) {
        tmp /= k;
        ++power;
      }
      mp[tmp].push_back(power + 1);
    }
  }

  for (map<int, vector<char> >::iterator it = mp.begin(); it != mp.end(); ++it) {
    ans += calc_for(it->first, it->second);
  }

  cout << ans << "\n";
  return 0;
}
