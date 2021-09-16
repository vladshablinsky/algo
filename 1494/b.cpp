#include <iostream>

using namespace std;

bool solve() {
  int n, u, r, d, l;
  scanf("%d%d%d%d%d", &n, &u, &r, &d, &l);


  auto check_mask = [n,u,r,d,l](int mask) mutable {
    printf("d: %d u: %d l: %d r: %d\n", d, u, l, r);

    if (mask & (1 << 3)) {
      --u;
      --l;
    }
    if (mask & (1 << 2)) {
      --u;
      --r;
    }
    if (mask & (1 << 1)) {
      --d;
      --l;
    }
    if (mask & 1) {
      --r;
      --d;
    }

    bool no_neg = u >= 0 && d >= 0 && l >= 0 && r >= 0;
    bool place_rest = u <= n - 2 && d <= n - 2 && l <= n - 2 && r <= n - 2;
    return no_neg && place_rest;
  };
  check_mask(1);
  printf("AFTER: d: %d u: %d l: %d r: %d\n", d, u, l, r);
  check_mask(2);
  printf("AFTER: d: %d u: %d l: %d r: %d\n", d, u, l, r);

  //for (int i = 0; i < (1 << 4); ++i) {
  //  if (check_mask(i)) {
  //    return true;
  //  }
  //}
  return false;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
