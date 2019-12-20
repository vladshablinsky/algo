//▄███████▀▀▀▀▀▀███████▄
//░▐████▀▒ЗАПУСКАЕМ▒▀██████▄
//░███▀▒▒▒▒▒ДЯДЮ▒▒▒▒▒▒▀█████
//░▐██▒▒▒▒▒▒БОГДАНА▒▒▒▒▒████▌
//░▐█▌▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒████▌
//░░█▒▄▀▀▀▀▀▄▒▒▄▀▀▀▀▀▄▒▐███▌
//░░░▐░░░▄▄░░▌▐░░░▄▄░░▌▐███▌
//░▄▀▌░░░▀▀░░▌▐░░░▀▀░░▌▒▀▒█▌
//░▌▒▀▄░░░░▄▀▒▒▀▄░░░▄▀▒▒▄▀▒▌
//░▀▄▐▒▀▀▀▀▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒█
//░░░▀▌▒▄██▄▄▄▄████▄▒▒▒▒█▀
//░░░░▄██████████████▒▒▐▌
//░░░▀███▀▀████▀█████▀▒▌
//░░░░░▌▒▒▒▄▒▒▒▄▒▒▒▒▒▒▐
//░░░░░▌▒▒▒▒▀▀▀▒▒▒▒▒▒▒▐

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;
int n, m, d;
const int N = 110000;
vector<int> ed[N];
vector<int> ob[N];
string open[N];
int marker, colors;
int visited[N];
int f[N * 51];
int sz[N * 51];
bool used[N][50];
int color[N][50];
vector<pair<int, int> > ord;
void go(int v, int t) {
    used[v][t] = true;
    int nxt = t + 1;
    while (nxt >= d) {
        nxt -= d;
    }
    for (auto to: ed[v]) {
        if (used[to][nxt]) {
            continue;
        }
        go(to, nxt);
    }
    ord.emplace_back(v, t);
}
void dfs(int v, int t) {
    color[v][t] = colors;
    if (open[v][t] == '1') {
        if (visited[v] != marker) {
            f[colors]++;
            sz[colors]++;
            visited[v] = marker;
        }
    }
    int nxt = t - 1;
    while (nxt < 0) {
        nxt += d;
    }
    for (auto to: ob[v]) {
        if (color[to][nxt] != 0) {
            continue;
        }
        dfs(to, nxt);
    }
}
int main() {
    freopen("input.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
    //ios_base::sync_with_stdio(false);
    cin >> n >> m >> d;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        ed[u].push_back(v);
        ob[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cin >> open[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < d; j++) {
            if (used[i][j] == 0) {
                go(i, j);
            }
        }
    }
    reverse(ord.begin(), ord.end());
    for (auto it: ord) {
        if (color[it.first][it.second] == 0) {
            colors++;
            marker++;
            dfs(it.first, it.second);

        }
    }

    reverse(ord.begin(), ord.end());
    for (auto it: ord) {
        int v = it.first;
        int t = it.second;
        int nxt = t + 1;
        while (nxt >= d) {
            nxt -= d;
        }
        for (auto to: ed[v]) {
            if (color[to][nxt] == color[v][t]) {
                continue;
            } else {
                f[color[v][t]] = max(f[color[v][t]], f[color[to][nxt]] + sz[color[v][t]]);
            }
        }
    }
    cout << f[color[1][0]] << "\n";
    return 0;
}
