#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int query(int a, int b, int c, int d) {
  int cnt_intersections;
  cout << "? " << a << " " << b << " " << c << " " << d << "\n";
  cin >> cnt_intersections;
  return cnt_intersections;
}

int find_in_row(int y, int n, int l, int r) {
  int m = (l + r) / 2;

  if (l == r) {
    return l;
  }


  if (query(y, l, y, m) & 1) {
    return find_in_row(y, n, l, m);
  } else {
    return find_in_row(y, n, m + 1, r);
  }
}

int find_in_column(int x, int n, int u, int d) {
  int m = (u + d) / 2;
  if (u == d) {
    return u;
  }
  // cout << "u: " << u << ", d: " << d << ", m: " << m << endl;
  if (query(u, x, m, x) & 1) {
    return find_in_column(x, n, u, m);
  } else {
    return find_in_column(x, n, m + 1, d);
  }
}

int main() {
  int n;
  cin >> n;

  int x1 = -1, y1 = -1, x2 = -1, y2 = -1;
  for (int i = 1; i <= n; ++i) {
    if (x1 == -1 && i == n) {
      continue;
    }

    int odd = query(i, 1, i, n) & 1;
    if (x1 == -1 && odd) {
      int x = find_in_row(i, n, 1, n);
      x1 = x;
      y1 = i;
    } else if (x1 != -1 && odd) {
      int x = find_in_row(i, n, 1, n);
      x2 = x;
      y2 = i;
      cout << "! " << y1 << " " << x1 << " " << y2 << " " << x2 << "\n";
      cout.flush();
      return 0;
    }
  }

  for (int j = 1; j <= n; ++j) {
    int odd = query(1, j, n, j) & 1;
    if (x1 == -1 && odd) {
      int y = find_in_column(j, n, 1, n);
      x1 = j;
      y1 = y;
    } else if (x1 != -1 && odd) {
      int y = find_in_column(j, n, 1, n);
      x2 = j;
      y2 = y;

      cout << "! " << y1 << " " << x1 << " " << y2 << " " << x2 << "\n";
      cout.flush();
      return 0;
    }
  }
  return 0;
}
