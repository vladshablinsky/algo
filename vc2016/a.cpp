#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
  int r, c, n, k;
  pair<int, int> alts[20];
  int ans = 0;
  cin >> r >> c >> n >> k;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    alts[i] = make_pair(x, y);
  }

  for (int i = 1; i <= r; ++i) {
    for (int j =1; j <= c; ++j) {
      for (int ii = i; ii <= r; ++ii) {
        for (int jj = j; jj <= c; ++jj) {
          int cnt_on_photo = 0;
          for (int l = 0; l < n; ++l) {
            int xx = alts[l].first;
            int yy = alts[l].second;
            if (xx >= i && xx <= ii && yy >= j && yy <= jj) {
              ++cnt_on_photo;
            }
          }
          if (cnt_on_photo >= k) {
            ++ans;
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
