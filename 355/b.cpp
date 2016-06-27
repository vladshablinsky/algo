#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int NAT_VAL = 4096;
int f[12][12];
int n;

int add_vine() {
  int ans = 0;
  f[1][1] += NAT_VAL;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      if (f[i][j] >= NAT_VAL) {
        ++ans;
        int extra = f[i][j] - NAT_VAL;
        f[i][j] -= extra;
        f[i + 1][j] += extra / 2;
        f[i + 1][j + 1] += extra / 2;
      }
    }
  }
  return ans;
}

void print_vine() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      cout << f[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  int t;
  int ans = 0;
  cin >> n >> t;

  for (int i = 0; i < t; ++i) {
    ans = add_vine();
  }

  //print_vine();

  cout << ans << endl;

  return 0;
}
