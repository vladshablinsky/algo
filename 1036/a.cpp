#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  long long n, k;
  cin >> n >> k;
  cout << k / n + ((k % n) != 0) << "\n";
  return 0;
}
