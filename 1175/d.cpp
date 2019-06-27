#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main() {
  int n, k;
  vector<long long> v;
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    long long t;
    cin >> t;
    v.push_back(t);
  }

  long long sum = 0;
  for (int i = (int)v.size() - 1; i >= 0; --i) {
    v[i] = sum + v[i];
    sum = v[i];
  }

  long long ans = sum;
  multiset<long long> st;
  for (int i = 1; i < v.size(); ++i) {
    st.insert(v[i]);
    if (st.size() > k - 1) {
      st.erase(st.begin());
    }
  }

  for (long long el: st) {
    ans += el;
  }
  cout << ans << "\n";
  return 0;
}
