#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

constexpr int kMaxN = 200005;
constexpr int kL = 18;

int tin[kMaxN];
int tout[kMaxN];
int timer{0};

int up[kMaxN][kL];
vector<int> g[kMaxN];

bool is_upper(int a, int b) {
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void dfs(int v, int p) {
  tin[v] = ++timer;



  for (auto to: g[v]) {
    if (to != p) {
      up[to][0] = v;
      for (int j = 1; j < kL; ++j) {
        up[to][j] = up[up[to][j - 1]][j - 1];
      }

      dfs(to, v);
    }
  }
  tout[v] = ++timer;
}

int lca_impl(int a, int b) {
  if (is_upper(a, b)) { return a; }
  if (is_upper(b, a)) { return b; }
  for (int j = kL - 1; j >= 0; --j) {
    if (!is_upper(up[a][j], b)) {
      a = up[a][j];
    }
  }
  return up[a][0];
}

int lca(int a, int b) {
  int ans = lca_impl(a, b);
  // cout << "lca " << a << "," << b << ": " << ans << endl;
  return ans;
}

bool is_between_impl(int a, int b, int u) {
  if (!is_upper(a, b)) {
    swap(a, b);
  }
  if (is_upper(a, b)) {
    return is_upper(a, u) && is_upper(u, b);
  }
  return false;
}

bool is_between(int a, int b, int u) {
  int ans = is_between_impl(a, b, u);
  //printf("is_between(%d,%d,%d): %d\n", a, b, u, ans);
  return ans;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  //for (int i = 0; i < n; ++i) {
  //  cout << "from " << i + 1 << ": " << endl;
  //  for (auto to: g[i]) {
  //    cout << to + 1  << " ";
  //  }
  //  cout << endl;
  //}

  dfs(0, -1);

  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < 6; ++j) {
  //     printf("up[%d][%d]: %d, ", i, j, up[i][j]);
  //   }
  //   printf("\n");
  // }

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);
    int a, b;
    bool cur_ans = true;
    scanf("%d", &a);
    b = a;

    if (k > 1) {
      scanf("%d", &b);
    }

    --a;--b;
    int c = lca(a, b);
    bool starts_in_lca = (a == c || b == c);
    if (c == a) {
      swap(a, b);
    }

    for (int i = 0; i < k - 2; ++i) {
      int u;
      scanf("%d", &u);
      --u;
      if (cur_ans) {
        if (is_upper(a, u)) {
          a = u;
        }

        if (!starts_in_lca) {
          if (is_upper(b, u)) {
            b = u;
          }
          cur_ans &= (is_between(a, c, u) || is_between(b, c, u));
        } else {
          if (!is_between(a, c, u)) {
            int lca1 = lca(a, u);
            int lca2 = lca(b, u);

            if (lca1 != lca2) {
              cur_ans = false;
            } else {
              c = lca1;
              b = u;
              starts_in_lca = (c == b);
            }
          }
        }
      }
    }

    if (cur_ans) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}

