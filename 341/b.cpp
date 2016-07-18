#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

const int MAX_N = 2e5 + 5;
map<int, int> mp1;
map<int, int> mp2;
pair<int, int> a[MAX_N];

void proceed(int x, int y) {
  mp1[x + y]++;
  mp2[x - y]++;
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    proceed(x, y);
    a[i] = make_pair(x, y);
  }

  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    int x = a[i].first, y = a[i].second;
    ans += (mp1[x + y] - 1);
    ans += (mp2[x - y] - 1);
  }

  cout << ans / 2 << "\n";
  return 0;
}

