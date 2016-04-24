#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

long long n;
long long q;
int cnt_sec = 0;
long long sum = 0;

int main() {
  cin >> n >> q;

  for (int i = 0; i < q; ++i) {
    int q;
    long long x;
    cin >> q;
    if (q == 1) {
      cin >> x;
      sum += x;
    }
    else {
      ++cnt_sec;
    }
  }

  for (long long i = 0; i < n; i += 2) {
    long long f = (i - sum + n) % n;
    long long s = (i + 1 - sum + n) % n;
    if (cnt_sec % 2 == 1) {
      swap(f, s);
    }
    cout << f + 1 << " " << s + 1 << " ";
  }
  cout << "\n";

  return 0;
}
