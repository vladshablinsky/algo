#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<int> st;
vector<int> v;

int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    v.push_back(t);
  }

  sort(v.begin(), v.end());
  int cur_max = 0;
  for (int i = 0; i < v.size(); ++i) {
    if (cur_max < v[i]) {
      cur_max++;
    }
  }

  cout << cur_max + 1 << "\n";
  return 0;
}


