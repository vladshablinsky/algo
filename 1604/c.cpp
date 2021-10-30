#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

bool solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }

  while (v.size()) {
    int moves = 0;
    while (moves < v.size() && (*(v.rbegin() + moves) % (v.size() + 1 - moves) == 0)) {
      ++moves;
    }

    if (moves == v.size()) {
      return false;
    }

    // cout << "remove: " << *(v.end() - moves - 1) << endl;
    v.erase(v.end() - moves - 1);
  }

  return true;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
