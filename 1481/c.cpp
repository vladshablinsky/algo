#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

const int MAXN = 100005;
int a[MAXN];
int b[MAXN];
int c[MAXN];
int target_cnt[MAXN];
int plank_with_color[MAXN];
vector<int> to_repaint[MAXN];

bool solve(vector<int>& ans) {
  int n, m;
  scanf("%d%d", &n, &m);

  int cnt_to_repaint = 0;
  unordered_set<int> st;
  for (int i = 1; i <= n; ++i) {
    plank_with_color[i] = 0;
    to_repaint[i].clear();
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
    plank_with_color[b[i]] = i;
    if (a[i] != b[i]) {
      ++cnt_to_repaint;
      to_repaint[b[i]].push_back(i);

      st.insert(i);
    }
  }

  // Read c & Solve
  int last_foreground_painter = 0;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &c[i]);
    if (plank_with_color[c[i]]) {
      last_foreground_painter = i;
    }
  }

  for (int i = 1; i <= m; ++i) {
    if (to_repaint[c[i]].size()) {
      // repaint
      int plank_idx = to_repaint[c[i]].back();
      plank_with_color[c[i]] = plank_idx;

      ans.push_back(plank_idx);
      to_repaint[c[i]].pop_back();

      st.erase(plank_idx);
    } else if (int plank_idx = plank_with_color[c[i]]) {
      // paint same color
      ans.push_back(plank_idx);
    } else if (!st.empty()){
      // paint the one that will be repainted later
      ans.push_back(*st.begin());
    } else if (last_foreground_painter > i) {
      ans.push_back(plank_with_color[c[last_foreground_painter]]);
    }
  }

  return ans.size() == m && st.empty();
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    vector<int> ans;
    if (solve(ans)) {
      printf("YES\n");
      for (auto target: ans) {
        printf("%d ", target);
      }
      printf("\n");
    } else {
      printf("NO\n");
    }
  }
}
