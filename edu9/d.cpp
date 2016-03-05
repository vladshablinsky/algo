#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> > a;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    if (t <= m) {
      a.push_back(make_pair(t, i));
    }
  }


  return 0;
}
