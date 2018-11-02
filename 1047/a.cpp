#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  int n;
  cin >> n;
  int a = 1;
  int b = 1;
  int c = n - 2;
  if (c % 3 == 0) {
    ++b;
    --c;
  }
  cout << a << " " << b << " " << c << "\n";
  return 0;
}
