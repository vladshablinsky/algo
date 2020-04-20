#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1005;

int main() {
  int n, r;
  cin >> n >> r;
  vector<int> st;
  st.push_back(-r);

  for (int i = 0; i < n; ++i) {
    int has_heater;
    cin >> has_heater;
    if (has_heater) {
      while (st.size() >= 2 && *next(st.rbegin()) + r >= i - r + 1) {
        st.pop_back();
      }

      if (st.back() + r < i - r + 1) {
        cout << -1 << "\n";
        return 0;
      }

      st.push_back(i);
      if (i + r - 1 >= n - 1) {
        cout << st.size() - 1 << "\n";
        return 0;
      }
    }
  }
  cout << -1 << "\n";
  return 0;
}
