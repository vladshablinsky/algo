#include <iostream>

using namespace std;

long long solve() {
  int x, y;
  cin >> x >> y;
  y = min(x, y);

  long long ans = 0;
  for (int k = 1; k + 1 <= y && k * 1ll * (k + 2) <= x; ++k) {
    // numbers are of form
    // k * (b + 1) <= x
    // b: k < b <= y

    int income = min(x / k, y + 1); // b + 1 can't be more than y + 1
    income -= (k + 1); // substract k * t <= x, when t <= k + 1 because b > k
    ans += max(income, 0);
  }
  return ans;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
