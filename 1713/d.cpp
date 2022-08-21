#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int query(int a, int b) {
  int result;
  cout << "? " << a << " " << b << "\n";
  cin >> result;
  if (!result) {
    return 0;
  }
  return result == 1 ? a : b;
}

void answer(int winner) {
  cout << "! " << winner << "\n";
  cout.flush();
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> cur;
  vector<int> new_cur;
  cur.reserve(1 << n);
  if (n > 2) {
    new_cur.reserve(1 << (n - 2));
  }
  for (int i = 1; i <= 1 << n; ++i) {
    cur.push_back(i);
  }

  while (cur.size() >= 4) {
    new_cur.clear();
    for (int i = 0; i < cur.size(); i += 4) {
      int a = cur[i];
      int b = cur[i + 2];

      auto query1 = query(a, b);
      if (!query1) {
        a = cur[i + 1];
        b = cur[i + 3];
      } else if (query1 == a) {
        b = cur[i + 3];
      } else {
        a = cur[i + 1];
      }
      new_cur.push_back(query(a, b));
    }
    swap(cur, new_cur);
  }

  if (cur.size() == 1) {
    answer(cur.front());
  } else {
    answer(query(cur[0], cur[1]));
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
