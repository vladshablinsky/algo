#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

int n;
int a[105];

void make_swap(int l, int r) {
  cout << l + 1 << " " << r + 1 << "\n";
  for (int i = l; i < r; ++i) {
    swap(a[i], a[i + 1]);
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }

  for (int i = n - 1; i >= 1; --i) {
    int cur_max = a[0];
    int cur_max_pos = 0;
    for (int j = 0; j <= i; ++j) {
      if (a[j] > cur_max) {
        cur_max = a[j];
        cur_max_pos = j;
      }
    }
    int l = cur_max_pos;
    int r = i;

    if (r - l + 1 <= 1) {
      continue;
    } else if ((r - l + 1) % 2 == 1) {
      make_swap(l, r - 1);
      make_swap(r - 1, r);
    } else {
      make_swap(l, r);
    }
  }

  cout << "RESULT \n";

  for (int i = 0; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << endl;

  return 0;
}
