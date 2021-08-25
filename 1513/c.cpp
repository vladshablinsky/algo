#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

const int MOD = 1000000007;

using mx = vector<vector<int>>;

unordered_map<int, shared_ptr<mx>> cache;

shared_ptr<mx> get_mx(int n, int m) {
  auto res = make_shared<mx>();
  res->resize(n);
  for (int i = 0; i < n; ++i) {
    (*res)[i] = vector<int>(m, 0);
  }
  return res;
}

shared_ptr<mx> get_e(int n) {
  auto res = get_mx(n, n);
  for (int i = 0; i < n; ++i) {
    (*res)[i][i] = 1;
  }
  return res;
}

shared_ptr<mx> mul(const shared_ptr<mx>& a, const shared_ptr<mx>& b) {
  int d1 = a->size();
  int d2 = (*a)[0].size();
  int d3 = (*b)[0].size();
  auto res = get_mx(d1, d3);
  for (int k = 0; k < d2; ++k) {
    for (int i = 0; i < d1; ++i) {
      if ((*a)[i][k] == 0) {
        continue;
      }
      for (int j = 0; j < d3; ++j) {
        (*res)[i][j] = ((*a)[i][k] * 1ll * (*b)[k][j] + (*res)[i][j]) % MOD;
      }
    }
  }
  return res;
}

auto trans = get_mx(10, 10);
void fill_trans() {
  for (int i = 0; i < 10; ++i) {
    (*trans)[(i - 1 + 10) % 10][i] = 1;
  }
  (*trans)[9][1] = 1;
}

shared_ptr<mx> binpow(int p) {
  if (cache.count(p)) {
    return cache[p];
  }

  if (p == 0) {
    cache[0] = get_e(trans->size());
  } else {
    shared_ptr<mx> res;
    if (p % 2) {
      res = mul(binpow(p - 1), trans);
    } else {
      res = binpow(p / 2);
      res = mul(res, res);
    }
    cache[p] = res;
  }
  return cache[p];
}

// we're sure we only
void solve(pair<int, int>& inp) {
  static auto res = trans;
  static auto x = get_mx(1, 10);
  static int power = 1;

  // Fill the number
  for (int i = 0; i < 10; ++i) {
    (*x)[0][i] = 0;
  }
  do {
    (*x)[0][inp.first % 10]++;
    inp.first /= 10;
  } while (inp.first != 0);

  // Multiply up to desired power
  if (inp.second != power) {
    res = mul(res, binpow(inp.second - power));
    power = inp.second;
  }

  auto result_row = mul(x, res);
  int ans = 0;
  for (int i = 0; i < 10; ++i) {
    ans = (ans + (*result_row)[0][i]) % MOD;
  }

  inp.second = ans;
}

int main() {
  fill_trans();
  int t;
  scanf("%d", &t);
  vector<pair<pair<int, int>, int>> q;
  for (int i = 0; i < t; ++i) {
    int n, m;
    scanf("%d%d", &n, &m);
    q.push_back({{n, m}, i});
  }
  sort(q.begin(), q.end(), [](auto &a, auto& b) { return a.first.second < b.first.second; });
  for (auto& el: q) {
    solve(el.first);
  }
  sort(q.begin(), q.end(), [](auto &a, auto& b) { return a.second < b.second; });
  for (auto& el: q) {
    printf("%d\n", el.first.second);
  }
}
