#include <iostream>
#include <cstdio>

using namespace std;

const string kAshish{"Ashish"};
const string kUtkarsh{"Utkarsh"};

bool check(long long x, long long y, long long d) {
  if (x < 0 || y < 0) {
    return false;
  }
  return x * x + y * y <= d * d;
}

// true if ashish wins
bool solve() {
  int d, k;
  scanf("%d%d", &d, &k)d

  // find diagonal point.
  int x = 0;
  int y = 0;
  int i = -1;
  while (check(x, y, d)) {
    if (i & 1) {
      x += k;
    } else {
      y += k;
    }
    ++i;
  }

  int parity = i & 1;

  cout << "i: " << i << endl;
  y = (i + 1) / 2 * k;
  x = (i / 2) * k;

  cout << "x: " << x << ", y: " << y << endl;

  if (check(x - k, y - k, d)) {
    parity ^= 1;
  }
  return parity == 1;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      cout << kAshish << "\n";
    } else {
      cout << kUtkarsh << "\n";
    }
  }
}
