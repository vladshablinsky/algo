#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

const double EPS = 1e-6;
map<int, int> points;

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    if (points.count(x)) {
      points[x] = max(points[x], y);
    } else {
      points[x] = y;
    }
  }


  vector<pair<int, int>> ans_points;
  ans_points.push_back(*points.begin());

  auto it = next(points.begin());
  while (it != points.end()) {
    //cout << "Now cur point is " << it->first << " " << it->second << endl;
    if (ans_points.size() == 1) {
      ans_points.push_back(*it);
      ++it;
      //cout << "just add sceond point\n";
    } else {
      int last_idx = (int)ans_points.size() - 1;
      double x1 = ans_points[last_idx].first;
      double x2 = ans_points[last_idx - 1].first;

      double dy = ans_points[last_idx].second - ans_points[last_idx - 1].second;

      double b = dy / (x1 - x2) - x1 - x2;
      double c = - x1 * (b + x1) + ans_points[last_idx].second;

      double cur_x = it->first;
      double cur_y = it->second;

      double cur_parabola_y = cur_x * (cur_x + b) + c;
      if (cur_y - EPS > cur_parabola_y) {
        //cout << "cur points higher than last parabola, so remove last point\n";
        ans_points.pop_back();
      } else {
        //cout << "cur points lower than last parabola, so add point to ans\n";
        if (abs(cur_y - cur_parabola_y) < EPS) {
          // add higher point!
          ans_points.pop_back();
        }
        ans_points.push_back(*it);
        ++it;
      }
    }
  }

  cout << ans_points.size() - 1 << "\n";

  return 0;
}
