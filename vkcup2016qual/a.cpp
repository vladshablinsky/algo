#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

map<int, pair<int, int> > mp;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    mp[t] = make_pair(mp[t].first + 1, i + 1);
  }
  int ans = -1;
  int ans_id;
  int ans_time;
  for (map<int, pair<int, int> >::iterator it = mp.begin(); it != mp.end(); ++it) {
    int id = it->first;
    int cnt = (it->second).first;
    int stamp = (it->second).second;
    if (cnt > ans) {
      ans = cnt;
      ans_id = id;
      ans_time = stamp;
    } else if (cnt == ans && ans_time > stamp) {
      ans_time = stamp;
      ans_id = id;
    }
  }
  cout << ans_id << "\n";

  return 0;
}
