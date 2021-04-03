#include <iostream>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 405;
const int INF = 1e9;
const int MAXC = 27;
int f[MAXN][MAXN];
// closest_c[i][j] -- closest position of j to the right
// standing at position i in string s
int closest_c[MAXN][MAXC];

void init_closest_c(const string& s) {
  for (int i = 0; i < MAXC; ++i) {
    closest_c[s.length()][i] = INF;
  }

  for (int i = (int)s.length() - 1; i >= 0; --i) {
    for (int j = 0; j < MAXC; ++j) {
      closest_c[i][j] = closest_c[i + 1][j];
    }
    closest_c[i][s[i] - 'a'] = i + 1;
  }

   // set<char> symbols(s.begin(), s.end());

   // for (auto el: symbols) {
   //   cout << "closest " << el << endl;
   //   for (int i = 0; i <= s.length(); ++i) {
   //     cout << closest_c[i][el - 'a'] << " ";
   //   }
   //   cout << endl;
   // }

   // cout << "============\n";

}

void init_stuff(int n, int m) {
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      f[i][j] = INF;
    }
  }
}

bool solve_substr(const string &a, const string &b) {
  init_stuff(a.length(), b.length());
  f[0][0] = 0;

  for (int i = 0; i <= a.length(); ++i) {
    for (int j = 0; j <= b.length(); ++j) {
      if (i + j == 0) {
        continue;
      }
      if (j - 1 >= 0 && f[i][j - 1] < INF) {
        f[i][j] = min(f[i][j], closest_c[f[i][j - 1]][b[j - 1] - 'a']);
      }

      if (i - 1 >= 0 && f[i - 1][j] < INF) {
        f[i][j] = min(f[i][j], closest_c[f[i - 1][j]][a[i - 1] - 'a']);
      }
      // cout << "f[" << i << "][" << j <<  "] = " << f[i][j] << " ";
    }
    // cout << endl;
  }
  return f[a.size()][b.size()] < INF;
}

void solve(const string &s, const string &t) {
  if (s.length() < t.length()) {
    cout << "NO\n";
    return;
  }

  if (t.length() == 0) {
    cout << "YES\n";
    return;
  }

  for (int i = 0; i < t.length(); ++i) {
    if (solve_substr(t.substr(0, i), t.substr(i, t.length() - i))) {
      // cout << "OK FOR " << i << endl;
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  //freopen("input2.txt", "r", stdin);

  int t_cnt;
  string s, t;
  cin >> t_cnt;

  while (t_cnt--) {
    cin >> s >> t;
    // cout << s << " " << t << endl;

    init_closest_c(s);

    solve(s, t);
  }

  return 0;
}
