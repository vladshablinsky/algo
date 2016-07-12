#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 2e5 + 5;
map<int, int> mp;
int ans = 1;
int cnt_awesome = 0;
int cnt_ok = 0;

int b[MAX_N], c[MAX_N];


int main() {
  int n, m;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    mp[t]++;
  }

  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &b[i]);
  }
  for (int i = 0; i < m; ++i) {
    scanf("%d", &c[i]);
  }

  for (int i = 0; i < m; ++i) {
    int cur_cnt_aw = mp[b[i]];
    int cur_cnt_ok = mp[c[i]];
    if (cur_cnt_aw > cnt_awesome) {
      ans = i + 1;
      cnt_awesome = cur_cnt_aw;
      cnt_ok = cur_cnt_ok;
    } else if (cur_cnt_aw == cnt_awesome) {
      if (cur_cnt_ok > cnt_ok) {
        ans = i + 1;
        cnt_ok = cur_cnt_ok;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}
