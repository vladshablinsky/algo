#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 20;
int fact[MAXN];

void init_fact() {
  fact[0] = 1;
  for (int i = 1; i < MAXN; ++i) {
    fact[i] = fact[i - 1] * i;
  }
}

int rec(int i, int n, int k, set<int>& numbers, vector<int>& ans) {
  if (i == 0) {
    return k;
  }

  numbers.insert(i);
  // cout << "fact(" << n - i + 1 << ") = " << fact[n - i + 1] << endl;
  if (fact[n - i + 1] < k) {
    k = rec(i - 1, n, k, numbers, ans);
  }

  if (fact[n - i + 1] < k) {
    return k;
  }

  int cnt_skip_prev = k / fact[n - i];
  int rem = k % fact[n - i];
  int idx = cnt_skip_prev - (rem == 0) + (k == 0);

  auto it = numbers.begin();
  for (int i = 0; i < idx; ++it, ++i) {}

  ans[i - 1] = *it;
  numbers.erase(*it);

  // took last permutation of length n - i + 1; Should propagate!
  if (rem == 0 && i != n) {
    rem = fact[n - i];
  }
  return rem;
}

vector<int> get_permutation(int n, int k) {
  vector<int> v(n, 0);
  for (int i = 0; i < n; ++i) {
    v[i] = i + 1;
  }

  set<int> s;
  if (rec(n, n, k, s, v)) {
    return {};
  }
  return v;
}

int main() {
  init_fact();
  int n, k;
  cin >> n >> k;
  auto ans = get_permutation(n, k);

  cout << "{";
  for (auto el: ans) {
    cout << el << ", ";
  }
  cout << "}\n";

  return 0;
}
