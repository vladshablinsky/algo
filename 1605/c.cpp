#include <iostream>
#include <cstdio>

using namespace std;

void upd(int& a, int& b, int& c, char symbol, bool add=true) {
  int k = add ? 1 : -1;
  a += (symbol == 'a') * k;
  b += (symbol == 'b') * k;
  c += (symbol == 'c') * k;
}

int solve() {
  int n;
  string s;
  scanf("%d", &n);
  cin >> s;

  int a = 0;
  int b = 0;
  int c = 0;

  int r = 0;
  int l = 0;
  for (int r = 0; i < n; ++i) {
    upd(a, b, c, s[r]);
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
