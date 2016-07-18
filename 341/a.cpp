#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  long long sum = 0;
  int min_odd = 1e9 + 5;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    sum += t;
    if (t % 2) {
      min_odd = min(min_odd, t);
    }
  }

  if (sum % 2) {
    cout << sum - min_odd << "\n";
  } else {
    cout << sum << "\n";
  }
  return 0;
}
