#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

const int MAXN = 2005;
int m[MAXN][MAXN];
int d[MAXN][MAXN];
bool used[MAXN];
int n;

void update_used() {
  for (int i = 0; i < n; ++i) {
    used[i] = false;
  }
}

void dfs(int s, int)

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == '1') {
        m[i][j] = 1;
      }
    }
  }



}
