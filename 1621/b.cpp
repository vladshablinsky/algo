#include <iostream>
#include <cstdio>

using namespace std;

const int INF = 1000000000;

struct Seg {
  int l;
  int r;
  int c;
  bool operator==(const Seg& other) {
    return l == other.l && r == other.r && c == other.c;
  }
};

void solve() {
  int n;
  scanf("%d", &n);

  Seg mostleft{INF, INF, INF};
  Seg mostright{0, 0, INF};
  Seg longest{0, INF, INF};

  for (int i = 0; i < n; ++i) {
    int l, r, c;
    scanf("%d%d%d", &l, &r, &c);
    if (l < mostleft.l) {
      mostleft = {l, r, c};
      longest = mostleft;
    } else if (l == mostleft.l) {
      if (c < mostleft.c) {
        mostleft.r = r;
        mostleft.c = c;
      }

      if (r > longest.r) {
        longest.r = r;
        longest.c = c;
      } else if (r == longest.r) {
        longest.c = min(longest.c, c);
      }
    }

    if (r > mostright.r) {
      mostright = {l, r, c};
    } else if (r == mostright.r && c < mostright.c) {
      mostright.l = l;
      mostright.c = c;
    }

    // Output:
    if (mostleft == mostright) {
      printf("%d\n", mostleft.c);
    } else if (longest.r == mostright.r) {
      printf("%d\n", min(longest.c, mostleft.c + mostright.c));
    } else {
      printf("%d\n", mostleft.c + mostright.c);
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
