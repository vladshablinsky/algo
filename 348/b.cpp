#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = 1e5 + 10;
int n;
string s;
int a[MAXN];
bool used[MAXN];

void dfs(int x) {
  used[x] = true;
  int k = 1;
  if (s[x] == '<') {
    k = -1;
  }
  int next = x + k * a[x];
  if (next < 0 || next >= n) {
    cout << "FINITE\n";
    exit(0);
  }
  if (used[next]) {
    cout << "INFINITE\n";
    exit(0);
  }
  dfs(next);
}

int main() {
  cin >> n;
  cin >> s;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  dfs(0);
  cout << "INFINITE\n";
  return 0;
}
