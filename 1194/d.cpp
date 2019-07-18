#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>

using namespace std;

// True means the one who makes first move wins.
bool solve() {
  long long n, k;
  cin >> n >> k;

  if (k == 3) {
    return n % 4;
  } else if (k % 3) {
    return n % 3;
  } else {
    int idx = ((n * k + n - n / k + n % k) % (k + 1));
    return idx % 3 || idx == k;
  }
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    if (solve()) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }

  return 0;
}
