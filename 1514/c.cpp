#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
int main() {
  int n;
  cin >> n;

  vector<int> ps;
  long long product = 1;
  for (int i = 1; i < n; ++i) {
    if (gcd(n, i) == 1) {
      ps.push_back(i);
      product *= i;
      product %= n;
    }
  }

  cout << ps.size() - (product != 1) << "\n";
  for (auto p: ps) {
    if (p != product || p == 1) {
      cout << p << " ";
    }
  }
  cout << "\n";
}
