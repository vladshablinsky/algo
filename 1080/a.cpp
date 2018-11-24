#include <iostream>
#include <vector>

using namespace std;

int main() {
  long long n, k;
  cin >> n >> k;
  long long ans = 0;
  cout << (8 * n + k - 1) / k + (5 * n + k - 1) / k + (2 * n + k - 1) / k << endl;
  return 0;
}
