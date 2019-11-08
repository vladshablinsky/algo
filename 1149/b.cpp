#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int MAX_L = 252;
const int MAX_N = 100005;
const int ABC_SIZE = 'z' - 'a' + 1;
const int INF = 1e9;
int f[MAX_L][MAX_L][MAX_L];
int closest_chars[MAX_N][ABC_SIZE];
vector<string> cur_s(3);

void init_f() {
  f[0][0][0] = -1;
}

int& f_proxy(const vector<int> &idx) {
  return f[idx[0]][idx[1]][idx[2]];
}

void init_closest_chars(const string &s) {
  vector<int> cur_closest(ABC_SIZE, INF);
  for (int i = 0; i < MAX_N; ++i) {
    for (int j = 0; j < ABC_SIZE; ++j) {
      closest_chars[i][j] = INF;
    }
  }
  for (int i = (int)s.length() - 1; i >= 0; --i) {
    cur_closest[s[i] - 'a'] = i;
    for (int j = 0; j < ABC_SIZE; ++j) {
      closest_chars[i][j] = cur_closest[j];
    }
  }
}

int main() {
  int n, m;
  string s;
  scanf("%d%d", &n, &m);
  cin >> s;

  init_closest_chars(s);
  init_f();

  for (int q_id = 0; q_id < m; ++q_id) {
    char query_type, value;
    int religion_id;
    cin >> query_type >> religion_id;
    --religion_id;

    int next_rel_id = (religion_id + 1) % 3;
    int prev_rel_id = (religion_id + 2) % 3;
    int mx_i = cur_s[next_rel_id].length();
    int mx_j = cur_s[prev_rel_id].length();
    int mx_k = cur_s[religion_id].length();
    vector<int> composite_idx(3);

    if (query_type == '-') {
      cur_s[religion_id].pop_back();
      --mx_k;
    } else {
      cin >> value;

      cur_s[religion_id].push_back(value);
      ++mx_k;

      for (int i = 0; i <= mx_i + mx_j + 1; ++i) {
        int ii = min(i, mx_i);
        int jj = max(0, i - mx_i);


        // can increase jj no more than mx_i times
        // can decrease ii no more than mx_j times
        while (ii >= 0 && jj <= mx_j) {
          auto &idx = composite_idx;
          composite_idx[next_rel_id] = ii;
          composite_idx[prev_rel_id] = jj;
          composite_idx[religion_id] = mx_k - 1;
          int ans = INF;
          int f_res = f_proxy(composite_idx);
          if (f_res != INF) {
            ans = closest_chars[f_res + 1][value -'a'];
          }


          composite_idx[next_rel_id] = ii - 1;
          composite_idx[religion_id] = mx_k;
          if (ii - 1 >= 0) {
            f_res = f_proxy(composite_idx);
            if (f_res != INF) {
              ans = min(ans, closest_chars[f_res + 1][cur_s[next_rel_id][ii - 1] - 'a']);
            }
          }

          composite_idx[next_rel_id] = ii;
          composite_idx[prev_rel_id] = jj - 1;
          if (jj - 1 >= 0) {
            f_res = f_proxy(composite_idx);
            if (f_res != INF) {
              ans = min(ans, closest_chars[f_res + 1][cur_s[prev_rel_id][jj - 1] - 'a']);
            }
          }

          composite_idx[prev_rel_id] = jj;
          f_proxy(composite_idx) = ans;

          // iterate
          --ii; ++jj;
        }
      }
    }

    composite_idx[next_rel_id] = mx_i;
    composite_idx[prev_rel_id] = mx_j;
    composite_idx[religion_id] = mx_k;
    if (f_proxy(composite_idx) != INF) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
  return 0;
}


