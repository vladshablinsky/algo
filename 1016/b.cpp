#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
  int n, m, q;
  string s, t;
  cin >> n >> m >> q;
  cin >> s >> t;

  vector<int> v(n);
  int prev = 0;
  for (int i = 0; i + t.length() - 1 < s.length(); ++i) {
    v[i] = prev + (s.substr(i, t.length()) == t);
    prev = v[i];
  }

  for (int i = 0; i < q; ++i) {
    int ll, rr;
    cin >> ll >> rr;
    --ll;--rr;
    int r = rr - t.length() + 1;
    int l = ll - 1;
    if (l >= r) {
      cout << 0 << "\n";
    } else {
      cout << (r >= 0 ? v[r] : 0) - (l >= 0 ? v[l]: 0) << "\n";
    }
  }
  return 0;
}
