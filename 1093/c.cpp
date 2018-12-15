#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1000000000 * 1ll * 1000000000 + 1;
int main() {
  int n;
  cin >> n;
  vector<long long> a(n);
  long long prev_a = 0;
  long long next_last_a = INF;
  for (int i = 0; i < n / 2; ++i) {
    long long b_i;
    cin >> b_i;
    long long cur_a = prev_a;
    long long cur_last_a = b_i - cur_a;
    if (next_last_a < cur_last_a) {
      cur_a += cur_last_a - next_last_a;
      cur_last_a = b_i - cur_a;
    }
    a[i] = cur_a;
    a[n - i - 1] = cur_last_a;
    prev_a = a[i];
    next_last_a = cur_last_a;
  }

  for (auto &el: a) {
    cout << el << " ";
  }
  cout << "\n";
  return 0;
}
