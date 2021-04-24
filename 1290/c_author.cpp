#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define fi first
#define se second
using namespace std;

const int N = 1E6 + 5, K = 1E6 + 5, INF = 1E9 + 7;

int n, k, c, v, ans = 0, dsu[K];
char s[N];
vector<int> adj[N];

struct node {
    int l, r, xo;

    node(int _l = 0, int _r = 0, int _xo = 0) : l(_l), r(_r), xo(_xo) {}

    int get() {
        return min(l, r);
    }

    inline void operator+=(node oth) {
        l = min(INF, l + oth.l);
        r = min(INF, r + oth.r);
    }
} val[K];

pair<int, int> trace(int u) {
  cout << "trace " << u << " dsu[u]: " << dsu[u] << endl;
    if (dsu[u] < 0) {
        cout << "dsu < 0, return " << u << endl;
        return {u, 0};
    } else {
        pair<int, int> tmp = trace(dsu[u]);
        dsu[u] = tmp.fi;
        val[u].xo ^= tmp.se;
        return {dsu[u], val[u].xo};
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k >> (s + 1);
    for (int i = 1; i <= k; i++) {
        dsu[i] = -1;
        val[i] = node(1, 0, 0);
        cin >> c;
        while (c--) {
            cin >> v;
            adj[v].push_back(i);
        }
    }
    for (int i = 1; i <= n; i++) {
      cout << "i: " << i << endl;
        int typ = (s[i] - '0') ^ 1;
        if (ans != -1) {
            if (adj[i].size() == 1) {
                pair<int, int> u = trace(adj[i][0]);
                ans -= val[u.fi].get();
                val[u.fi] += node((u.se == typ) * INF, (u.se != typ) * INF);
                ans += val[u.fi].get();
            } else if (adj[i].size() == 2) {
              cout << "try trace: " << adj[i][0] << endl;
                pair<int, int> u = trace(adj[i][0]);
                cout << "try trace: " << adj[i][1] << endl;
                pair<int, int> v = trace(adj[i][1]);
                if (u.fi != v.fi) {
                    ans -= val[u.fi].get() + val[v.fi].get();

                    // ensure dsu[u] is smaller
                    if (dsu[u.fi] > dsu[v.fi]) {
                        swap(u, v);
                    }
                    if (u.se ^ v.se ^ typ) {
                      // turn on whole set and mark it turned on.
                        swap(val[v.fi].l, val[v.fi].r);
                        val[v.fi].xo = 1;
                    }
                    dsu[u.fi] += dsu[v.fi];
                    dsu[v.fi] = u.fi;
                    val[u.fi] += val[v.fi];
                    ans += val[u.fi].get();
                }
            }
        }
        cout << ans << '\n';
    }
}
