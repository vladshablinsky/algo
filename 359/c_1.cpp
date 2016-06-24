#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <set>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  int nn = n, mm = m;
  int c1 = 0, c2 = 0;
  while (nn != 0) {
    nn /= 7;
    ++c1;
  }
  while (mm != 0) {
    mm /= 7;
    ++c2;
  }
  if (c1 + c2 > )
}
