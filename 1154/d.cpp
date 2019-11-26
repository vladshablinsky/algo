#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
int s[MAXN];

int main() {
  int n, a, b;
  cin >> n >> b >> a;
  int cur_a = a;
  for (int j = 0; j < n; ++j) {
    cin >> s[j];
  }

  int i;
  for (i = 0; i < n; ++i) {
    if (cur_a + b == 0) {
      break;
    }

    if (cur_a == a) {
      --cur_a;
    } else {
      if (s[i]) {
        cur_a += (b != 0);
        cur_a -= (b == 0);
        b = max(0, b - 1);
      } else {
        b -= (cur_a == 0);
        cur_a = max(cur_a - 1, 0);
      }
    }
  }
  cout << i << "\n";
  return 0;
}
