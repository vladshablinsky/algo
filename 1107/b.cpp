#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    long long k, x;
    cin >> k >> x;
    cout << x + (k - 1) * 9 << endl;
  }
  return 0;
}
