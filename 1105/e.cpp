#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int MAXM = 42;
const int INF = 1e9;

int f[MAXN][MAXM];
vector<int> prev_max_prev(MAXM, -INF);
vector<int> cur_max_prev;
int counter = 0;

pair<int, int> queries[MAXN];
unordered_map<string, int> mp;

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int query_type;
    cin >> query_type;
    if (query_type != 1) {
      string name;
      cin >> name;
      if (!mp.count(name)) {
        mp[name] = ++counter;
      }
      queries[i].second = mp[name];
    }
    queries[i].first = query_type;
  }

  // debug
  //for (auto el: mp) {
  //  cout << el.first << " " << el.second << endl;
  //}


  prev_max_prev[0] = 0;

  // f(i, j) -- max number of friends satisfied if processed first i
  // events and vere processing first j friends.
  //
  // prev_max_prev(j) -- how many we can get from current i and of first j
  // friends so that we can change name right after that

  for (int i = 1; i <= n; ++i) {
    cur_max_prev = prev_max_prev;
    for (int j = 1; j <= m; ++j) {
      f[i][j] = max(f[i - 1][j], f[i][j - 1]);
      if (queries[i].first != 1 && queries[i].second == j) {
        f[i][j] = max(f[i][j], prev_max_prev[j - 1] + 1);
      } else if (queries[i].first == 1) {
        cur_max_prev[j] = max(cur_max_prev[j], f[i][j]);
      }
    }
    // upd
    swap(cur_max_prev, prev_max_prev);
  }

  // for (int i = 0; i <= n; ++i) {
  //   for (int j = 0; j <= m; ++j) {
  //     cout << f[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  // cout << "====\n";

  cout << f[n][m] << "\n";
  return 0;
}
