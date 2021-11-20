#include <iostream>
#include <vector>

using namespace std;

bool solve() {
  string s;
  cin >> s;

  vector<int> cnt(3, 0);
  for (auto el: s) {
    cnt[el - 'A']++;
  }

  return cnt[1] == cnt[0] + cnt[2];
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
