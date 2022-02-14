#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

void solve() {
  string s;
  cin >> s;

  vector<int> cnt('z' - 'a' + 1, 0);
  for (auto c: s) {
    cnt[c - 'a']++;
  }

  string ans;
  string middle;
  for (int i = 0; i < cnt.size(); ++i) {
    if (cnt[i] == 2) {
      ans.push_back(i + 'a');
    } else if (cnt[i] == 1) {
      middle.push_back(i + 'a');
    }
  }

  cout << ans + middle + ans << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
