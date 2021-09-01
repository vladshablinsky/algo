#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> ans;
  for (int i = k - 1; i >= (k + 1) / 2; --i) {
    ans.push_back(i);
  }
  for (int i = k + 1; i <= n; ++i) {
    ans.push_back(i);
  }
  cout << ans.size() << "\n";
  for (auto el: ans)  {
    cout << el << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
