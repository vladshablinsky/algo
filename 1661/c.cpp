#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

long long solve(const vector<int>& h, int target) {
  //cout << "yo!" << target << endl;
  int parity = target % 2;
  int parity_fixes = 0;
  long long sum = 0;
  long long ans = 0;
  for (auto el: h) {
    if (el % 2 != parity) {
      parity_fixes++;
    }
    sum += target - el;
  }
  sum -= parity_fixes;
  sum -= 2 * max(0, parity_fixes - 1);

  assert(sum % 2 == 0);
  ans = max(0, 2 * parity_fixes - 1);

  //cout << "sum : " << sum << ", parity: " << parity_fixes << ", ans: " << ans << endl;

  if (sum <= 0) {
    return ans;
  }



  bool first_even = parity_fixes != 0;
  ans += (sum / 3) * 2;
  int rem = (sum % 3);
  if (rem == 2 && !first_even) {
    ans += 2;
  } else if (rem) {
    ans += 1;
  }
  return ans;
}

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> h(n);
  int mx = 0;
  for(auto& el: h) {
    scanf("%d", &el);
    mx = max(mx, el);
  }

  cout << min(solve(h, mx), solve(h, mx + 1)) << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
