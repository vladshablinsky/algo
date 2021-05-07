#include <iostream>
#include <cstdio>

using namespace std;

const long long MAXA = 1000000;

bool is_prime(long long x) {
  if (x == 2 || x == 1) {
    return true;
  }
  for (long long i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      return false;
    }
  }
  return true;
}

void solve(long long a, long long b) {
  if (a % (a * b) == 0) {
    cout << "NO\n";
  } else {
    long long prime = 2 * b + 1;
    while (!is_prime(prime) || ((prime - b) % b == 0)) {
      ++prime;
    }
    cout << "YES\n";
    cout << a * b << " " << a * (prime - b) << " " << a * prime << "\n";
  }

}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    long long a, b;
    cin >> a >> b;
    solve(a, b);
  }

  return 0;
}
