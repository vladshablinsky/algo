#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = 200005;
const int NONE = -1;

int prev_idx[MAXN];
int next_idx[MAXN];
int mapping[MAXN];
int a[MAXN];
int layout[MAXN];
bool used[MAXN];

int main() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    mapping[a[i]] = i;
    next_idx[i] = i + 1;
    prev_idx[i] = i - 1;
  }
  next_idx[n - 1] = NONE;
  prev_idx[0] = NONE;

  int cur_max = n;
  int team = 0;
  while (cur_max != 0) {
    if (!used[cur_max]) {
      used[cur_max] = true;
      layout[mapping[cur_max]] = team;

      int prev_k_th_idx = -1;
      int next_k_th_idx = -1;
      int cur_idx = prev_idx[mapping[cur_max]];
      for (int i = 0; i < k; ++i) {
        if (cur_idx == -1) {
          break;
        }
        layout[cur_idx] = team;
        used[a[cur_idx]] = true;
        cur_idx = prev_idx[cur_idx];
      }

      prev_k_th_idx = cur_idx;
      cur_idx = next_idx[mapping[cur_max]];
      for (int i = 0; i < k; ++i) {
        if (cur_idx == -1) {
          break;
        }
        layout[cur_idx] = team;
        used[a[cur_idx]] = true;
        cur_idx = next_idx[cur_idx];
      }
      next_k_th_idx = cur_idx;

      if (prev_k_th_idx != -1) {
        next_idx[prev_k_th_idx] = next_k_th_idx;
      }
      if (next_k_th_idx != -1) {
        prev_idx[next_k_th_idx] = prev_k_th_idx;
      }

      team = (team + 1) % 2;
    }
    --cur_max;
  }
  for (int i = 0; i < n; ++i) {
    cout << layout[i] + 1;
  }
  cout << "\n";
  return 0;
}
