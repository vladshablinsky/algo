#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 2e5 + 5;

map<int, int> mp_x;
map<int, int> mp_y;
map<pair<int, int>, int> mp_xy;

int main() {
  long long ans = 0;
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int xx, yy;
    scanf("%d%d", &xx, &yy);
    mp_x[xx]++;
    mp_y[yy]++;
    mp_xy[make_pair(xx, yy)]++;
  }

  for (map<int, int>::iterator it = mp_x.begin(); it != mp_x.end(); ++it) {
    //printf("it first %d, itseoncd %d\n", it->first, it->second);
    ans += (it->second) * 1ll * (it->second - 1) / 2;
  }

  //printf("-==========-\n");

  for (map<int, int>::iterator it = mp_y.begin(); it != mp_y.end(); ++it) {
    //printf("it first %d, itseoncd %d\n", it->first, it->second);
    ans += (it->second) * 1ll * (it->second - 1) / 2;
  }

  for (map<pair<int, int>, int>::iterator it = mp_xy.begin(); it != mp_xy.end(); ++it) {
    //printf("it first %d, %d, itseoncd %d\n", (it->first).first, (it->first).second, it->second);
    ans -= (it->second) * 1ll * (it->second - 1) / 2;
  }

  cout << ans << "\n";

  return 0;
}
