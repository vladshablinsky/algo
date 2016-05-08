#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

void solve() {
  string ar[4] = {"00", "01", "10", "11"};
  int cnt[4];
  vector<pair<int, int> > cur_cnt(4);
  int len = 1;
  for (int i = 0; i < 4; ++i) {
    cin >> cnt[i];
    len += cnt[i];
    cur_cnt[i] = make_pair(cnt[i], i);
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) {
        cur_cnt[k] = make_pair(cnt[k], k);
      }


      if ((i != j && cur_cnt[i].first > 0 && cur_cnt[j].first > 0) ||
          (i == j && (cur_cnt[i].first > 1 || (len == 2 && cur_cnt[i].first == 1)))) {
        //cout << "new cycle" << endl;
        //cout << "start is " << ar[i] << " end is " << ar[j] << endl;
        cur_cnt[i].first--;
        cur_cnt[j].first--;
        string cur;
        cur += ar[i];
        //cout << "beginning is " << cur << endl;

        bool flag = true;
        while (flag) {
          sort(cur_cnt.rbegin(), cur_cnt.rend());
          flag = false;
          for (int k = 0; k < 4; ++k) {
            int kk = cur_cnt[k].second;
            if (ar[kk][0] == cur.back() && cur_cnt[k].first > 0) {
              cur.push_back(ar[kk][1]);
              --cur_cnt[k].first;
              flag = true;
              break;
            }
          }
        }
        if (cur.back() == ar[j][0]) {
          cur.push_back(ar[j][1]);
        }
        if (cur.length() == len) {
          cout << cur << "\n";
          return;
        }
      }
    }
  }
  cout << "impossible\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
