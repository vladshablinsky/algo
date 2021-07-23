#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool solve() {
  string s;
  int n;
  cin >> n;
  cin >> s;

  queue<int> t_idx;
  for (int i = 0; i < n; ++i) {
    if (s[i] == 'T') {
      t_idx.push(i);
    } else if (s[i] == 'M') {
      if (t_idx.empty()) {
        return false;
      }
      int idx = t_idx.front();
      t_idx.pop();
      s[idx] = '#';
    }
  }

  queue<int>().swap(t_idx);
  for (int i = n - 1; i >= 0; --i) {
    if (s[i] == 'T') {
      t_idx.push(i);
    } else if (s[i] == 'M') {
      if (t_idx.empty()) {
        return false;
      }
      int idx = t_idx.front();
      t_idx.pop();
      s[idx] = '#';
    }
  }

  return t_idx.empty();
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
