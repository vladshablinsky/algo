#include <iostream>
#include <vector>

using namespace std;

bool solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> both_days_cnt(5, vector<int>(5, 0));

  int x;
  for (int i = 0; i < n; ++i) {
    vector<int> all_i_can;
    for (int j = 0; j < 5; ++j) {
      scanf("%d", &x);
      if (x) {
        all_i_can.push_back(j);
      }
    }
    for (auto day1: all_i_can) {
      for (auto day2: all_i_can) {
        both_days_cnt[day1][day2]++;
      }
    }
  }

  for (int first_day = 0; first_day < 4; ++first_day) {
    if (int cnt_first = both_days_cnt[first_day][first_day]; cnt_first >= n / 2) {
      for (int second_day = 0; second_day < 5; ++second_day) {
        if (first_day == second_day) {
          continue;
        }

        int cnt_second_no_first = both_days_cnt[second_day][second_day] -
          both_days_cnt[first_day][second_day];
        int cnt_first_go_to_second = min(cnt_first - n / 2, both_days_cnt[first_day][second_day]);
        if (cnt_second_no_first + cnt_first_go_to_second >= n / 2) {
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
