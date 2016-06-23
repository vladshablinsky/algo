#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
  int n, x;
  char type;
  int cnt;
  int sad = 0;
  cin >> n >> x;
  long long left_cream = x;

  for (int i = 0; i < n; ++i) {
    cin >> type >> cnt;
    if (type == '-') {
      if (left_cream >= cnt) {
        left_cream -= cnt;
      } else {
        ++sad;
      }
    } else {
      left_cream += cnt;
    }
  }

  cout << left_cream << " " << sad << "\n";
  return 0;
}
