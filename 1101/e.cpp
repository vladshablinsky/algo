#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int q;
  scanf("%d", &q);
  int max_square_side = 0;
  int max_long_side = 0;
  for (int i = 0; i < q; ++i) {
    char c;
    int x, y;
    scanf(" %c ", &c);
    scanf("%d %d", &x, &y);
    //cin >> c >> x >> y;
    if (c == '+') {
      max_square_side = max(max_square_side, min(x, y));
      max_long_side = max(max_long_side, max(x, y));
    } else {
      if (max_square_side <= min(x, y) && max_long_side <= max(x, y)) {
        printf("YES\n");
        //cout << "YES\n";
      } else {
        printf("NO\n");
        //cout << "NO\n";
      }
    }
  }
  return 0;
}
