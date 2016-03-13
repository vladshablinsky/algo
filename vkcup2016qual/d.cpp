#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2e5 + 5;
int a[MAXN];

vector<pair<string, int> > ans;

int main() {
  int n, m, s, d;
  scanf("%d%d%d%d", &n, &m, &s, &d);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  sort(a, a + n);

  int cur_x = 0;
  int next = 0;

  while (cur_x != m) {
    //cout << "================\n";
    //cout << "CUR_X IS " << cur_x << endl;
    //cout << "NEXT IS " << next << endl;
    //cout << "A[NEXT]-cur_x-1 = " << a[next] - cur_x - 1 << endl;
  if (a[next] - cur_x - 1 < s) {
      printf("IMPOSSIBLE\n");
      return 0;
    } else {
      ans.push_back(make_pair("RUN", a[next] - cur_x - 1));
      cur_x = a[next] - 1;
      //cout << "CUR_X IS " << cur_x << endl;
      //cout << "GOING TO LOOP\n";
      while (next + 1 < n && a[next + 1] - a[next] - 2 < s) {
        ++next;
        //cout << "NEXT IS " << next << endl;
      }
      if (next + 1 == n) {
        //cout << "REACHING FINAL\n";
        if (a[n - 1] + 1 - cur_x <= d) {
          ans.push_back(make_pair("JUMP", a[n - 1] + 1 - cur_x));
          cur_x = a[n - 1] + 1;
          if (m - cur_x != 0) {
            ans.push_back(make_pair("RUN", m - cur_x));
          }
          cur_x = m;
        } else {
          printf("IMPOSSIBLE\n");
          return 0;
        }
      } else {
        if (a[next] + 1 - cur_x <= d) {
          ans.push_back(make_pair("JUMP", a[next] + 1 - cur_x));
          cur_x = a[next] + 1;
          next++;
        } else {
          printf("IMPOSSIBLE\n");
          return 0;
        }
      }
    }
  }

  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i].first << " " << ans[i].second << "\n";
  }

  return 0;
}
