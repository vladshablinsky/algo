#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
int p[MAXN];
int c[MAXN];
int restore[MAXN];

void upd_for_loop(vector<int> &loop, int &ans) {
  int m = loop.size();

  //cout << "loop is ";
  //for (auto el: loop) {
  //  cout << el << " ";
  //}
  //cout << endl;

  for (int i = 1; i <= m; ++i) {
    if (m % i == 0) {
      for (int start = 0; start < i; ++start) {
        bool flag = true;
        for (int pos = start; pos + i < m; pos += i) {
          if (c[loop[pos]] != c[loop[pos + i]]) {
            flag = false;
            break;
          }
        }

        if (flag) {
          ans = min(i, ans);
          break;
        }
      }
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i]);
  }

  int ans = n;
  vector<bool> used(n + 1, false);
  for (int i = 1; i <= n; ++i) {
    int cur_v = i;
    if (!used[cur_v]) {
      vector<int> loop;
      do {
        loop.push_back(cur_v);
        used[cur_v] = true;
        cur_v = p[cur_v];
      } while(!used[cur_v]);

      upd_for_loop(loop, ans);
    }
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
