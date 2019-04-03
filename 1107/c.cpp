#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main() {
  long long res = 0;

  int n, k;
  cin >> n >> k;
  vector<int> damage(n);
  string s;
  for (int i = 0; i < n; ++i) {
    cin >> damage[i];
  }
  cin >> s;

  for (int i = 0; i < n; ++i) {
    multiset<int, std::greater<int>> st;
    st.insert(damage[i]);
    while (i + 1 < n && s[i + 1] == s[i]) {
      st.insert(damage[i + 1]);
      ++i;
    }

    for (int j = 0, cnt = min(k, (int)st.size()); j < cnt; ++j) {
      res += *st.begin();
      st.erase(st.begin());
    }
  }
  cout << res << "\n";
  return 0;
}
