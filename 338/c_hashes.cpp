#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

const int MAX_N = 2200;

const int p = 37;
const int MOD = 1e9 + 9;

int p_pow[MAX_N];
int t_hash[MAX_N];
int s_hash[MAX_N];
int u_hash[MAX_N];
int power;
string s, t, u;

void init() {
  p_pow[0] = 1;
  for (int i = 1; i < MAX_N; ++i) {
    p_pow[i] = p_pow[i - 1] * 1ll * p;
  }
}

void calc_hashes(string &str, int *a) {
  //cout << "calculating hashes for " << str << endl;
  for (int i = 0; i < str.length(); ++i) {
    a[i] = (str[i] - 'a' + 1) * 1ll * p_pow[i];
    if (i > 0) {
      a[i] = a[i - 1] + a[i];
    }
    //cout << "h[ " << i << " ] is " << a[i] << endl;
  }
}

int get_hash(int l, int r, int *a) {
  int ans = a[r];
  if (l) {
    ans = ans - a[l - 1];
  }
  ans = ans * 1ll * p_pow[power - r];
  return ans;
}

unordered_map<int, pair<int, int>> mp;
vector<pair<int, int>> ans;

int main() {
  init();
  cin >> s >> t;
  power = max(s.length(), t.length()) - 1;
  u = s;
  reverse(u.begin(), u.end());

  calc_hashes(s, s_hash);
  calc_hashes(u, u_hash);
  calc_hashes(t, t_hash);

  for (int i = 0; i < s.length(); ++i) {
    for (int j = i; j < s.length(); ++j) {
      mp[get_hash(i, j, s_hash)] = make_pair(i + 1, j + 1);
      mp[get_hash(i, j, u_hash)] = make_pair(s.length() - i, s.length() - j);
    }
  }

  int cur_pos = 0;
  while (cur_pos < t.length()) {
    int l = cur_pos;
    int r = t.length() - 1;
    int pos = -1;
    while (l <= r) {
      int m = (l + r) / 2;
      int cur_substr = get_hash(cur_pos, m, t_hash);

      if (mp.find(cur_substr) != mp.end()) {
        pos = max(pos, m);
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    if (pos == -1) {
      cout << "-1\n";
      return 0;
    } else {
      ans.push_back(mp[get_hash(cur_pos, pos, t_hash)]);
    }
    cur_pos = pos + 1;
  }

  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d %d\n", ans[i].first, ans[i].second);
  }

  return 0;
}
