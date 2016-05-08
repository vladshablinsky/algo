#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 60;
int a[MAXN][MAXN];
int b;

void init() {
  for (int i = 0; i < b; ++i) {
    for (int j = 0; j < b; ++j) {
      a[i][j] = 0;
    }
  }
}

void solve(int id) {
  long long m;
  cin >> b >> m;
  init();
  cout << "Case #" << id << ": ";

  if (m > (1ll << (b - 2))) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  vector<int> v;
  a[0][b - 1] = 1;
  --m;
  long long mm = m;
  while (mm != 0) {
    v.push_back(mm % 2);
    mm /= 2;
  }

  for (int i = 0; i < v.size(); ++i) {
    int from = b - 2 - i;
    for (int j = from + 1; j < b; ++j) {
      a[from][j] = 1;
    }
  }

  for (int i = 0; i < v.size(); ++i) {
    int from = b - 2 - i;
    if (v[i] == 1) {
      a[0][from] = 1;
    }
  }

  cout << "POSSIBLE\n";
  for (int i = 0; i < b; ++i) {
    for (int j = 0; j < b; ++j) {
      cout << a[i][j];
    }
    cout << "\n";
  }
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
