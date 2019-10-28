#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  int max_depth = 0;
  int cur_depth = 0;
  for (int i = 0; i < n; ++i) {
    cur_depth += (s[i] == '(');
    cur_depth -= (s[i] == ')');
    max_depth = max(max_depth, cur_depth);
  }

  cur_depth = 0;
  for (int i = 0; i < n; ++i) {
    cur_depth += (s[i] == '(');
    cur_depth -= (s[i] == ')');
    if (cur_depth > max_depth / 2) {
      cout << 1;
      --cur_depth;
    } else if (cur_depth < 0) {
      cout << 1;
      ++cur_depth;
    } else {
      cout << 0;
    }
  }
  cout << "\n";
  return 0;
}
