#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

bool solve() {
  int len;
  string a, b;
  cin >> len;
  cin >> a >> b;
  int diff = 0; // 1 goes as +1, 0 goes as -1. Target diff is 0;
  int inv = 0;

  if (len % 2) {
    ++len;
    a.push_back('0');
    b.push_back('0');
  }
  for (auto c: a) {
    diff += c == '1';
    diff -= c == '0';
  }

  for (int i = len - 1; i >= 0; i -= 2) {
    if ((a[i] ^ inv) != b[i]) {
      if (!diff) {
        inv ^= 1;
      } else {
        return false;
      }
    }

    // odd position, no way to change it saving suffix.
    if ((a[i - 1] ^ inv) != b[i - 1]) {
      return false;
    }

    diff -= a[i] == '1';
    diff += a[i] == '0';
    diff -= a[i - 1] == '1';
    diff += a[i - 1] == '0';
  }

  return true;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    if (solve()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}
