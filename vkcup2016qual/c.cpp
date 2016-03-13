#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<string> v;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    v.push_back(s);
  }
  int ans = 6;
  for (int i = 0; i < v.size(); ++i) {
    for (int j = 0; j < v.size(); ++j) {
      if (i == j) {
        continue;
      }
      int cnt_diff = 0;
      for (int k = 0; k < 6; ++k) {
        cnt_diff += v[i][k] != v[j][k];
      }
      ans = min(ans, (cnt_diff + 1) / 2);
    }
  }
  if (n == 1) {
    cout << 6 << "\n";
    return 0;
  }
  cout << max(0, ans - 1) << "\n";

  return 0;
}
