#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  int carry = m;
  for (int i = 0; i < n; ++i) {
    int cur;
    cin >> cur;
    if (carry > cur) {
      carry -= cur;
      cout << 0 << " ";
      continue;
    } else {
      cur -= carry;
      cout << 1 + cur / m << " ";
      carry = m - (cur % m);
    }
  }
  return 0;
}
