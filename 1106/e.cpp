#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>

using namespace std;

const long long INF = 1000000000 * 1ll * 1000000000;
const int MAXN = 100003;
const int MAXM = 201;

const int OPEN = 0;
const int CLOSED = 1;

long long f[MAXM][MAXN];
int w[MAXN];
int d[MAXN];
int w_at[MAXN];
int d_at[MAXN];

vector<pair<int, int>> dqs[MAXN];


void init_f(int n, int m) {
  for (int j = 0; j <= m; ++j) {
    for (int i = 0; i <= n + 1; ++i) {
      f[j][i] = INF;
    }
  }
  for (int j = 0; j <= m; ++j) {
    f[j][1] = 0;
  }
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < k; ++i) {
    int s_i, t_i;
    scanf("%d%d%d%d", &s_i, &t_i, &d[i], &w[i]);
    dqs[s_i].push_back({i, OPEN});
    dqs[t_i + 1].push_back({i, CLOSED});
  }
  //cout << "read\n";

  set<int> st;
  multiset<pair<int, int>> ordered;
  for (int i = 1; i <= n; ++i) {
    //cout << "day: " << i << endl;
    for (auto &el: dqs[i]) {
      int id = el.first;
      //cout << "id: " << id << " ";
      if (el.second == CLOSED) {
        //cout << "closes.";
        st.erase(id);
        ordered.erase(ordered.find({w[id], d[id]}));
      } else {
        //cout << "opens.";
        st.insert(id);
        ordered.insert({w[id], d[id]});
      }
      //cout << endl;
    }

    if (!ordered.empty()) {
      w_at[i] = ordered.rbegin()->first;
      d_at[i] = ordered.rbegin()->second;
    } else {
      d_at[i] = i;
    }
  }

  init_f(n, m);
  for (int j = 0; j <= m; ++j) {
    for (int i = 1; i <= n; ++i) {
      f[j][d_at[i] + 1] = min(f[j][d_at[i] + 1], f[j][i] + w_at[i]);
      if (j + 1 <= m) {
        f[j + 1][i + 1] = min(f[j + 1][i + 1], f[j][i]);
      }
    }
  }

  cout << f[m][n + 1] << "\n";
  return 0;
}
