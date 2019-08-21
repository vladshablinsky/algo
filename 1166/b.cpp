#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s = "aeiou";

void print_table_in_line(int n, int m) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << s[(i + j) % s.length()];
    }
  }
  cout << "\n";
}

int main() {
  int k;
  cin >> k;
  for (int i = 5; i * i <= k; ++i) {
    if (k % i == 0) {
      print_table_in_line(i, k / i);
      return 0;
    }
  }
  cout << "-1\n";
  return 0;
}
