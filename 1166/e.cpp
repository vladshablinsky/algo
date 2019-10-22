#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  int n, m;
  cin >> m >> n;
  vector<unordered_set<int>> ls(m);
  for (int i = 0; i < m; ++i) {
    int k;
    cin >> k;
    for (int j = 0; j < k; ++j) {
      int el;
      cin >> el;
      ls[i].insert(el);
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < i; ++j) {
      bool any = false;
      for (auto el: ls[i]) {
        if (ls[j].count(el)) {
          any = true;
          break;
        }
      }
      if (!any) {
        cout << "impossible\n";
        return 0;
      }
    }
  }

  cout << "possible\n";
  return 0;
}
