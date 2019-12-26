#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5005;

vector<pair<int, int>> v;
pair<int, int> most_right_painted[MAXN];

int main() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    v.push_back({l, r});
  }

  sort(v.begin(), v.end());
  int all_painted = 0;
  for (int i = 0; i < q; ++i) {
    if (i) {
      most_right_painted[i] = most_right_painted[i - 1];

      if (most_right_painted[i].first < v[i - 1].second) {
        most_right_painted[i].first = v[i - 1].second;
      }
      if (most_right_painted[i].first > most_right_painted[i].second) {
        swap(most_right_painted[i].first, most_right_painted[i].second);
      }
    }

    if (v[i].second > most_right_painted[i].second) {
      all_painted += (v[i].second - max(v[i].first, most_right_painted[i].second + 1) + 1);
    }
  }

  for (int i = 0; i < q; ++i) {
    cout << "most_right_painted " << most_right_painted[i].first << " " << most_right_painted[i].second << endl;
  }

  cout << "all_painted is " << all_painted << endl;
  int ans = 0;
  for (int i = 0; i < q - 1; ++i) {
    int cur_ans = all_painted;
    cout << "trying to remove (" << v[i].first << ", " << v[i].second << ")\n";

    int first_hole_l = max(v[i].first, most_right_painted[i].second + 1);
    int first_hole_r = min(v[i].second, v[i + 1].first - 1);
    cur_ans -= max(0, first_hole_r - first_hole_l + 1);

    cout << "hole: (" << first_hole_l << ", " << first_hole_r << ")\n";

    for (int j = i + 1; j < q; ++j) {
      cout << "also removing (" << v[j].first << ", " << v[j].second << ")\n";

      int second_hole_l = v[j].first;
      if (most_right_painted[j].second == v[i].second) {
        second_hole_l = max(second_hole_l, most_right_painted[j].first + 1);
      } else {
        second_hole_l = max(second_hole_l, most_right_painted[j].second + 1);
      }
      int second_hole_r = v[j].second;
      if (j + 1 < q) {
        second_hole_r = min(v[j].second, v[j + 1].first - 1);
      }

      cout << "second hole: (" << second_hole_l << ", " << second_hole_r << ")\n";
      ans = max(ans, cur_ans - max(0, second_hole_r - second_hole_l + 1));
    }
  }
  cout << ans << "\n";
  return 0;
}
