#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAXN = 300005;
const int INF = 1e9;

int back_edges[MAXN];
int max_height[MAXN];
int p[MAXN];
int d[MAXN];

void init(int n) {
  for (int i = 0; i <= n; ++i) {
    p[i] = d[i] = -1;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  init(n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &max_height[n - i - 1]);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &back_edges[n - i - 1]);
  }

  // mostright element we can reach + from where we go before we slip
  int cur_mostright = max_height[0];
  int cur_prev = 0;
  int next_mostright = cur_mostright;
  int next_prev = 1;
  p[0] = -1;
  d[0] = 0;

  // NOTE: p is the node we got to i from before the slip
  for (int i = 1; i <= n && i <= cur_mostright; ++i) {
    // cout << "p[" << i << "]: " << cur_prev << endl;
    p[i] = cur_prev;
    d[i] = d[cur_prev] + 1;

    int slip_to = i - back_edges[i];
    if (int cur_right = slip_to + max_height[slip_to]; cur_right > next_mostright) {
      next_mostright = cur_right;
      next_prev = i;
    }

    if (i == cur_mostright) {
      // cout << "finishing: mostright will be now: " << next_mostright << endl;
      cur_prev  = next_prev;
      cur_mostright = next_mostright;
    }
  }

  if (p[n] != -1) {
    vector<int> path;

    int last_v = n;
    while (last_v != 0) {
      path.push_back(n - last_v);
      last_v = p[last_v];
    }
    reverse(path.begin(), path.end());

    printf("%d\n", path.size());
    for (auto v: path) {
      printf("%d ", v);
    }
    printf("\n");
  } else {
    printf("-1\n");
  }
}
