#include <iostream>
#include <cstdio>

using namespace std;

void solve() {
  int n;
  int h;
  cin >> n >> h;
  pair<int, int> best{0, 0};
  int el;
  for (int i = 0; i < n; ++i) {
    cin >> el;
    if (el > best.first) {
      best.second = best.first;
      best.first = el;
    } else if (el > best.second) {
      best.second = el;
    }
  }

  // cout << "best: " << best.first << " "<< best.second << endl;

  int ans = h / (best.first + best.second);
  h -= ans * (best.first + best.second);
  ans *= 2;
  if (h > best.first) {
    ans += 2;
  } else if (h > 0) {
    ++ans;
  }
  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
