#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
const int MAXN = 1005;
int a[MAXN], b[MAXN];
int n;

int main() {
  scanf("%d", &n);
    int f_1 = 0;
    int f_2 = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      f_1 |= a[i];
    }
    for (int i = 0; i < n; ++i) {
      scanf("%d", &b[i]);
      f_2 |= b[i];
    }
  cout << f_1 + f_2 << endl;

  return 0;
}
