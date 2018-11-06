#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int INF = 2e9 + 20;

int main() {
  int n, h;
  vector<pair<int, int>> flows;
  vector<int> pref;
  scanf("%d%d", &n, &h);

  for (int i = 0; i < n; ++i) {
    int x_l, x_r;
    scanf("%d%d", &x_l, &x_r);
    flows.push_back(make_pair(x_l, x_r));
  }

  int prev = 0;
  for (int i = 1; i < n; ++i) {
    pref.push_back(prev + flows[i].first - flows[i - 1].second);
    prev = pref.back();
    // cout << "prev is " << prev << endl;
  }
  pref.push_back(INF);

  int ans = h;
  for (int i = 0; i < n; ++i) {
    //cout << "i: " << i << endl;
    int pref_i = 0;
    if (i) {
      pref_i = pref[i - 1];
    }

    int most_right_flow_idx = n;

    int l = i;
    int r = n;
    while (l <= r) {
      int m = (l + r) / 2; // m is an index of current hole
      //cout << "m: " << m << " decrease: " << pref[m] - pref_i << endl;
      if (pref[m] - pref_i >= h) {
        most_right_flow_idx = min(most_right_flow_idx, m);
        r = m - 1;
      } else {
        l = m + 1;
      }
    }

    int h_decrease = 0;
    if (most_right_flow_idx - 1 >= 0) {
      h_decrease = pref[most_right_flow_idx - 1] - pref_i;
    }

    //cout << "most_right_flow_idx " << most_right_flow_idx << ", h_dec: " << h_decrease << endl;


    ans = max(ans, flows[most_right_flow_idx].second - flows[i].first + (h - h_decrease));
  }

  cout << ans << "\n";
  return 0;
}
