#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> primes;

bool is_prime(int x) {
  if (x == 1) return false;
  if (x == 2) return true;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

void prepare() {
  for (int i = 1; i <= 100; ++i) {
    if (is_prime(i)) {
      primes.push_back(i);
    }
  }
}

void solve() {
  string s;
  int idx_divisor = -1;
  for (int i = 0; i < 20; ++i) {
    cout << primes[i] << "\n";
    cin >> s;
    if (s == "yes") {
      idx_divisor = i;
      break;
    }
  }

  if (idx_divisor == -1) {
    cout << "prime\n";
    fflush(stdout);
    return;
  }

  for (int i = idx_divisor; primes[idx_divisor] * primes[i] <= 100; ++i) {
    cout << primes[idx_divisor] * primes[i] << "\n";
    cin >> s;
    if (s == "yes") {
      cout << "composite\n";
      fflush(stdout);
      return;
    }
  }
  cout << "prime\n";
  fflush(stdout);
  return;
}

int main() {
  prepare();
  solve();
  return 0;
}
