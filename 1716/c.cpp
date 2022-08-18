#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> up(n);
  vector<int> down(n);
  vector<int> zigzag;
  vector<int> updown;
  vector<int> downup;
  for (auto& el: up) {
    scanf("%d", &el);
  }
  for (auto& el: down) {
    scanf("%d", &el);
  }

  zigzag.push_back(up[0]);
  int up_idx = 1;
  int down_idx = 0;
  for (;;) {
    zigzag.push_back(down[down_idx++]);
    if (down_idx >= n) {
      break;
    }
    zigzag.push_back(down[down_idx++]);

    zigzag.push_back(up[up_idx++]);
    if (up_idx >= n) {
      break;
    }
    zigzag.push_back(up[up_idx++]);
  }
  updown = up;
  updown.insert(updown.end(), down.rbegin(), down.rend());

  downup = updown;
  downup.push_back(0);
  std::reverse(downup.begin(), downup.end());

  // time we need to wait before first move so we can walk through the vector
  auto wait_time = [](const vector<int>& v) {
    int cur_time = 0;
    int wait = 0;
    for (int i = 0; i + 1 < v.size(); ++i) {
      // cout << v[i] << " ";
      if (v[i + 1] > cur_time) {
        // wait for this time at index i
        wait += v[i + 1] - cur_time;
        cur_time = v[i + 1];
      }
      ++cur_time;
    }
    // cout << endl;
    return wait;
  };

  auto updown_wait = wait_time(updown);
  auto downup_wait = wait_time(downup);
  int ans = updown_wait + n + n - 1;

  //cout << "updown_wait " << updown_wait << endl;
  //cout << "downup_wait " << downup_wait << endl;

  int cur_time = 0;
  int init_cell_wait_time = 0;

  for (int i = 0; i + 1 < zigzag.size(); ++i) {
    //cout << "now on: " << zigzag[i] << endl;

    // number of points so far on the side of i'th point in zigzag.
    // If i'th point is up -> number of points up
    int cnt_this_side = (i + 2) / 2;
    int cnt_other_side = (i + 1) - cnt_this_side;

    //cout << "cnt this side: " << cnt_this_side << ", cnt other: " << cnt_other_side << endl;

    //cout << "init wait: " << init_cell_wait_time << endl;

    // now on the down side:
    if (i % 4 == 1) {
      ans = min(ans, init_cell_wait_time + max(0,
            downup_wait - init_cell_wait_time - cnt_other_side + 1));
    } else {
      ans = min(ans, init_cell_wait_time + max(0,
            updown_wait - init_cell_wait_time - cnt_other_side));
    }

    if (i + 1 < zigzag.size() && zigzag[i + 1] > cur_time) {
      init_cell_wait_time += (zigzag[i + 1] - cur_time);
      cur_time = zigzag[i + 1];
    }

    //cout << "now ans: " << ans << endl;

    // move
    cur_time++;
  }
  // cout << endl;

  printf("%d\n", ans + n + n - 1);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
