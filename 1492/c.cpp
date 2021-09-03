#include <iostream>
#include <vector>

using namespace std;

const int INF = 100000000;

int main() {
  int n, m;
  string s;
  string l;
  cin >> n >> m;
  cin >> s;
  cin >> l;
  vector<int> idx;
  int s_i = 0;
  for (auto c: l) {
    while (s[s_i] != c) {
      ++s_i;
    }
    idx.push_back(s_i++);
  }

  s_i = n - 1;
  int ans = 0;
  for (int i = m - 1; i >= 0; --i) {
    while (s[s_i] != l[i]) {
      --s_i;
    }

    if (i) {
      ans = max(ans, s_i - idx[i - 1]);
    }
    --s_i;
  }

  cout << ans << "\n";
}
