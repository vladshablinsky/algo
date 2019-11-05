#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAXN = 500005;
const int MOD = 1e9 + 7;
vector<int> a;
unordered_map<int, int> squeezed;
int tree_l[MAXN];
int tree_r[MAXN];
int n;

void inc_l(int pos, int val) {
  for (; pos < n; pos = (pos | (pos + 1))) {
    tree_l[pos] = (tree_l[pos] + val) % MOD;
  }
}

void inc_r(int pos, int val) {
  for (; pos < n; pos = (pos | (pos + 1))) {
    tree_r[pos] = (tree_r[pos] + val) % MOD;
  }
}

int sum_l(int i) {
  int sum = 0;
  for (; i >= 0; i = (i & (i + 1)) - 1) {
    sum = (sum + tree_l[i]) % MOD;
  }
  return sum;
}

int sum_r(int i) {
  int sum = 0;
  for (; i >= 0; i = (i & (i + 1)) - 1) {
    sum = (sum + tree_r[i]) % MOD;
  }
  return sum;
}

void squeeze() {
  vector<int> v = a;
  sort(v.begin(), v.end());
  for (int i = 0; i < n; ++i) {
    squeezed[v[i]] = i;
  }
}

int main() {
  scanf("%d", &n);
  a.resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  squeeze();

  int sum = 0;
  for (int i = 0; i < n; ++i) {
    inc_l(squeezed[a[i]], i + 1);
    long long add = ((n - i) * 1ll * sum_l(squeezed[a[i]] - 1)) % MOD;

    add = (add * a[i]) % MOD;
    sum = (sum + add) % MOD;
  }

  for (int i = n - 1; i >= 0; --i) {
    inc_r(squeezed[a[i]], (n - i));
    long long add = ((i + 1) * 1ll * sum_r(squeezed[a[i]] - 1)) % MOD;

    add = (add * a[i]) % MOD;
    sum = (sum + add) % MOD;

    // += a_i * i * (n - i)
    add = ((i + 1) * 1ll * (n - i)) % MOD;
    add = (add * a[i]) % MOD;

    sum = (sum + add) % MOD;
  }

  cout << sum << "\n";
  return 0;
}
