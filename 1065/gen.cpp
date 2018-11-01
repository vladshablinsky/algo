#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
  freopen("input.txt", "w", stdout);
  srand(time(0));
  int n = 1 + rand() % 20;
  int k = n + rand() % n;

  cout << n << " " << k << "\n";

  for (int i = 0; i < n; ++ i) {
    cout << 1 + rand() % 20 << " ";
  }
  return 0;
}
