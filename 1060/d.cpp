#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstdlib>

using namespace std;

typedef pair<int, pair<int, int>> lrid;

int main() {
  int n;
  cin >> n;

  long long ans = n;
  set<lrid, greater<lrid>> lefts;
  set<lrid, greater<lrid>> rights;
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    lefts.insert({l, {r, i}});
    rights.insert({r, {l, i}});
  }

  while (lefts.size()) {
    auto ll = *lefts.begin();
    auto rr = *rights.begin();

    int l1 = ll.first;
    int r1 = ll.second.first;
    int id1 = ll.second.second;
    int l2 = rr.second.first;
    int r2 = rr.first;
    int id2 = rr.second.second;

    lefts.erase(lefts.begin());
    rights.erase(rights.begin());
    lefts.erase({l2, {r2, id2}});
    rights.erase({r1, {l1, id1}});
    if (id1 == id2) {  // ids equal.
      ans += max(l1, r1);
    } else {
      ans += max(l1, r2);
      lefts.insert({l2, {r1, id1}});
      rights.insert({r1, {l2, id1}});
    }
  }
  cout << ans << "\n";
  return 0;
}
