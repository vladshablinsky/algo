#include <iostream>
#include <cstdio>
#include <memory>
#include <queue>

using namespace std;

const int MAXN = 105;
int grid[MAXN][MAXN];


inline pair<int, int> convert(int k) {
  return {k / 2, k % 2};
}

void add_cnt(
  int ii,
  int jj,
  vector<vector<int>>& ans,
  queue<int>& zeros,
  queue<int>& ones,
  int pop_zeros=0, int pop_ones=0
) {

  auto add = [&ii, &jj](int cnt, bool from_zeros, auto& ans, auto& zeros, auto& ones) {
    auto& target = from_zeros ? zeros : ones;
    auto& other = from_zeros ? ones: zeros;
    while (cnt--) {
      int k = target.front();
      auto [i, j] = convert(k);
      target.pop();

      grid[ii + i][jj + j] ^= 1;
      other.push(k);

      ans.back().push_back(ii + i + 1);
      ans.back().push_back(jj + j + 1);
    }
  };

  ans.push_back({});
  add(pop_zeros, true, ans, zeros, ones);
  add(pop_ones, false, ans, zeros, ones);
}

void process(int ii, int jj, vector<vector<int>>& ans, queue<int>& zeros, queue<int>& ones) {
  // cout << "process: " << ii << ", " << jj << endl;
  if (zeros.empty() && ones.empty()) {
    for (int k = 0; k < 4; ++k) {
      auto [i, j] = convert(k);
      if (grid[ii + i][jj + j]) {
        ones.push(k);
      } else {
        zeros.push(k);
      }
    }
  }

  if (ones.empty()) {
    return;
  }

  if (ones.size() >= 3) {
    add_cnt(ii, jj, ans, zeros, ones, 0, 3);
  } else {
    add_cnt(ii, jj, ans, zeros, ones, 2, 1);
  }

  process(ii, jj, ans, zeros, ones);
}

void process_two(const vector<pair<int, int>>& order, vector<vector<int>>& ans) {
  if (grid[order[0].first][order[0].second] +
      grid[order[1].first][order[1].second] == 0) {
    // cout << "yo: " << order[0].first << ", " << order[0].second << ", " << order[1].first << ", " << order[1].second;
    return;
  }

  ans.push_back({});
  int cnt_taken = 0;
  for (int k = 0; k < order.size(); ++k) {
    if (cnt_taken == 3) {
      break;
    }
    auto [i, j] = order[k];
    if (grid[i][j] == 1 || k >= 2) {
      ++cnt_taken;
      grid[i][j] ^= 1;
      ans.back().push_back(i + 1);
      ans.back().push_back(j + 1);
    }
  }
}

void process_9_9(int i, int j, vector<vector<int>>& ans) {
  process_two({{i, j}, {i + 1, j}, {i, j + 1}, {i + 1, j + 1}}, ans);
  queue<int> zeros;
  queue<int> ones;
  process(i, j + 1, ans, zeros, ones);

  process_two({{i + 1, j}, {i + 2, j}, {i + 1, j + 1}, {i + 2, j + 1}}, ans);
  queue<int>().swap(zeros);
  queue<int>().swap(ones);
  process(i + 1, j + 1, ans, zeros, ones);
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  string s;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    for (int j = 0; j < m; ++j) {
      grid[i][j] = s[j] - '0';
    }
  }

  vector<vector<int>> ans;
  bool propagate_down = false;
  for (int i = 0; i < n && !propagate_down; i += 2) {
    if (i + 3 == n) {
      propagate_down = true;
    }

    bool propagate_right = false;
    for (int j = 0; j < m && !propagate_right; j += 2) {
      if (j + 3 == m) {
        propagate_right = true;
      }

      queue<int> zeros;
      queue<int> ones;
      if (propagate_down + propagate_right == 1) {
        if (propagate_right) {
          process_two({{i, j}, {i + 1, j}, {i, j + 1}, {i + 1, j + 1}}, ans);
          process(i, j + 1, ans, zeros, ones);
        } else { // propagate_down
          process_two({{i, j}, {i, j + 1}, {i + 1, j}, {i + 1, j + 1}}, ans);
          process(i + 1, j, ans, zeros, ones);
        }
      } else if (propagate_down + propagate_down == 2) {
        process_9_9(i, j, ans);
      } else {
        // cout << "process: " << i << ", " << j << endl;
        process(i, j, ans, zeros, ones);
      }
    }
  }

  printf("%d\n", ans.size());
  for (auto& ans_row: ans) {
    for (auto el: ans_row) {
      printf("%d ", el);
    }
    printf("\n");
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
