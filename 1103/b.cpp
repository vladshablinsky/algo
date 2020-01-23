#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int INF = 1e9;

int main() {
  string s;
  char res;
  while ((cin >> s) && s != "end") {
    int ans = 1e9;
    int l = 1;
    int r = 2;
    int max_l = 1;

    cout << "? " << l << " " << r << "\n";
    cin >> res;
    if (res == 'x') {
      cout << "? " << 0 << " " << 1 << "\n";
      cin >> res;
      cout << "! " << 1 + (res == 'y') << "\n";
      continue;
    }
    l = 2;
    r = 4;

    do {
      cout << "? " << l << " " << r << "\n";
      cin >> res;
      if (res == 'y') {
        l *= 2;
        r *= 2;
      }
    } while (res == 'y' && l <= INF);

    while (r - l > 1) {
      int m = (r + l) / 2;

      cout << "? " << l << " " << m << "\n";
      cin >> res;
      if (res == 'x') {
        r = m;
      } else {
        l = m;
      }
    }
    cout << "? " << l << " " << r << "\n";
    cin >> res;
    if (res == 'x') {
      ans = r;
    } else {
      ans = l;
    }

    cout << "! " << ans << "\n";
  }

  fflush(stdout);
  return 0;
}
