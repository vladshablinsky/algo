#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 404;

void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> v;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      cin >> c;
      if (c == '*') {
        v.push_back({i, j});
      }
    }
  }

  if (v[0].first == v[1].first) {
    for (int i = 0; i < 2; ++i) {
      v.push_back(*next(v.rbegin()));
      v.back().first += 1;
      v.back().first %= n;
    }
  } else if (v[0].second == v[1].second) {
    for (int i = 0; i < 2; ++i) {
      v.push_back(*next(v.rbegin()));
      v.back().second += 1;
      v.back().second %= n;
    }
  } else {
    v.push_back(v[0]);
    v.push_back(v[1]);
    swap(v[3].first, v[2].first);
  }


  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      bool star = false;
      for (auto& el: v) {
        if (el == make_pair(i, j)) {
          star = true;
          cout << "*";
          break;
        }
      }
      if (!star) {
        cout << ".";
      }
    }
    cout << "\n";
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
