#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n;
  vector<int> a;
  multiset<int> b;

  scanf("%d", &n);
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < n; ++i) {
    int b_i;
    scanf("%d", &b_i);
    b.insert(b_i);
  }

  for (int i = 0; i < n; ++i) {
    auto lb = b.lower_bound(n - a[i]);
    if (lb == b.end()) {
      lb = b.begin();
    }

    cout << (a[i] + *lb) % n << " ";
    b.erase(lb);
  }
  cout << "\n";

  return 0;
}
