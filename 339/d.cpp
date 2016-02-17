#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 100000;

struct Data {
  int level;
  int cnt;
  long long sum_cnt;
  long long sum_cnt_mul_level;
  Data():
  level(0), cnt(0), sum_cnt(0), sum_cnt_mul_level(0) {};
  Data(int level, int cnt, long long sum_cnt, long long sum_cnt_mul_level):
    level(level), cnt(cnt), sum_cnt(sum_cnt), sum_cnt_mul_level(sum_cnt_mul_level) {};
};

struct MaximizeHelper {
  long long cnt_units_to_maximize;
  int level;
  int used_with_same_level;
  int cnt_left_diff_levels;
  MaximizeHelper():
  cnt_units_to_maximize(0),
    level(0),
    used_with_same_level(0),
    cnt_left_diff_levels(0) {};
  MaximizeHelper(long long cnt_units_to_maximize,
                 int level,
                 int used_with_same_level,
                 int cnt_left_diff_levels):
    cnt_units_to_maximize(cnt_units_to_maximize),
    level(level),
    used_with_same_level(used_with_same_level),
    cnt_left_diff_levels(cnt_left_diff_levels) {};
};

bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.second != b.second) {
    return a.second < b.second;
  } else {
    return a.first < b.first;
  }
}

long long units_to_set_min(int);
void update_the_force(MaximizeHelper, int, long long, int);

pair<int, int> array[MAXN + 5];
map<int, int> cnt;
/* sorted levels and cnts */
vector<Data> data_array;
vector<MaximizeHelper> maximize_helper;
long long n, c_f, c_m, max_level;
long long m;
long long ans = 0;
int ans_min;
int ans_to_max = 0;

int main() {
  // freopen("input.txt", "r", stdin);
  scanf("%lld%lld%lld%lld%lld", &n, &max_level, &c_f, &c_m, &m);

  for (int i = 0; i < n; ++i) {
    int tmp;
    scanf("%d", &tmp);
    array[i] = make_pair(tmp, i);
    cnt[tmp]++;
  }

  sort(array, array + n);

  //for (int i = 0; i < n; ++i) {
    //cout << array[i].first << " " << array[i].second << endl;
  //}

  for (map<int, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
    if (data_array.empty()) {
      data_array.push_back(Data(it->first, it->second, it->second, it->first * it->second));
    } else {
      data_array.push_back(Data(it->first,
                                    it->second,
                                    data_array.back().sum_cnt + it->second,
                                    data_array.back().sum_cnt_mul_level + it->first * it->second));
    }
  }

  //cout << "DATA_ARRAY===============\n";

  //for (int i = 0; i < data_array.size(); ++i) {
    //Data d = data_array[i];
    //printf("LEVEL-%d, CNT-%d, SUM_CNT-%lld, SUM_CNt*LEV-%lld\n", d.level, d.cnt, d.sum_cnt, d.sum_cnt_mul_level);
  //}

  maximize_helper.push_back(MaximizeHelper(0, 0, 0, data_array.size()));

  {
    int tmp = 0;
    for (map<int, int>::reverse_iterator it = cnt.rbegin(); it != cnt.rend(); ++it, ++tmp) {
      for (int i = 0; i < it->second; ++i) {
        //cout << "COST TO MAXIMIZE first " << maximize_helper.size() << " is " <<
          //maximize_helper.back().cnt_units_to_maximize + max_level - it->first << endl;

        maximize_helper.push_back(MaximizeHelper(
              maximize_helper.back().cnt_units_to_maximize + max_level - it->first,
              it->first,
              i + 1,
              data_array.size() - tmp - 1
              ));
      }
    }
  }

  //cout << "MAIMIZE_HELPER+++++++++\n";

  //for (int i = 0; i < maximize_helper.size(); ++i) {
    //MaximizeHelper mh = maximize_helper[i];
    //printf("UNITS TO MAX=%lld, LEVEL=%d, USED WITH SAME L=%d, LEFT=%d\n",  mh.cnt_units_to_maximize, mh.level, mh.used_with_same_level, mh.cnt_left_diff_levels);
  //}

  ans_min = data_array.front().level;
  if (data_array.front().level != max_level) {
    ans += data_array.front().level * 1ll * c_m;
  }
  if (data_array.back().level == max_level) {
    ans += data_array.back().cnt * c_f;
    ans_to_max = data_array.back().cnt;
  }

  //cout << "ans " << ans << " ans_min " << ans_min << " ans_to_max " << ans_to_max << endl;


  //cout << "STARTING MAIN LOOP\n";
  /* cnt we're going to set to max */
  for (int i = 0; i <= n; ++i) {
    //cout << "MAXIMIZE " << i << endl;
    MaximizeHelper helper_i = maximize_helper[i];

    long long free_units = m - helper_i.cnt_units_to_maximize;

    //cout << free_units << " units lefrt\n";
    if (free_units < 0) {
      break;
    }

    if (i == n) {
      long long force = c_f * 1ll * n + c_m * max_level;
      if (force > ans) {
        ans = force;
        ans_min = max_level;
        ans_to_max = n;
      }
      break;
    }

    /* binary search index of the minimum element */
    int l = 0;
    int r = helper_i.cnt_left_diff_levels;
    if (i == 0) {
      --r;
    }
    //cout << "L = " << l << " R = " << r << endl;
    while (l <= r) {
      int m = (l + r) / 2;
      long long needed = units_to_set_min(m);
      //cout << "NEEDED for " << m << " -- " << needed << endl;
      long long still_free = free_units - needed;
      if (still_free >= 0) {
        update_the_force(helper_i, m, still_free, i);
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
  }

  cout << ans << "\n";
  for (int i = 0; i < n; ++i) {
    if (array[i].first < ans_min) {
      array[i].first = ans_min;
    }
  }

  for (int i = n - 1, j = 0; j < ans_to_max; --i, ++j) {
    array[i].first = max_level;
  }

  sort(array, array + n, cmp);
  for (int i = 0; i < n; ++i) {
    printf("%d ", array[i].first);
  }
  printf("\n");

  return 0;
}

void update_the_force(MaximizeHelper mh,
                      int min_index,
                      long long still_free,
                      int cnt_maximized)
{
  //cout << "UPDATING THE FORCE\n";
  int level = data_array[min_index].level;
  long long cnt_on_min;
  long long force;
  int level_add;

  if (level == mh.level) {
    //cout << "F*** YOU\n";
    cnt_on_min = data_array[min_index].sum_cnt - mh.used_with_same_level;
    level_add = (int)(still_free / cnt_on_min);
    if (level + level_add < max_level) {
      force = c_m * (level + level_add) + c_f * cnt_maximized;
      if (force > ans) {
        ans = force;
        ans_min = level + level_add;
        ans_to_max = cnt_maximized;
      }
    }
  } else {
    int level_res = level + level_add;
    level_add = (int)(still_free / data_array[min_index].sum_cnt);
    if (min_index + 1 < data_array.size()) {
      if (level + level_add < data_array[min_index + 1].level) {
        force = c_m * (level + level_add) + c_f * cnt_maximized;
        level_res = level + level_add;
      } else {
        force = c_m * (data_array[min_index + 1].level - 1) + c_f * cnt_maximized;
        level_res = data_array[min_index + 1].level - 1;
      }
    } else if (level + level_add < max_level) {
      force = c_m * (level + level_add) + c_f * cnt_maximized;
      level_res = level + level_add;
    } else {
      force = c_m * max_level + c_f * cnt_maximized;
      level_res = max_level;
    }

    if (force > ans) {
      ans = force;
      ans_min = level_res;
      ans_to_max = cnt_maximized;
    }
  }
  //cout << "NOW FORCE IS " << ans << " ANS_MIN IS " << ans_min << " ANS TO MAX " << ans_to_max << endl;
}

long long units_to_set_min(int k) {
  //cout << "IN UNITS TO SET MINIMUN TO THE K_TH LEVEL\n";
  if (k == 0) {
    //cout << "k = 0\n";
    return 0;
  } else {
    return data_array[k - 1].sum_cnt * data_array[k].level - data_array[k - 1].sum_cnt_mul_level;
  }
}
