#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 300005;
int sieve[MAXN]; // max prime divisor except 1

void init_sieve() {
  for (int i = 2; i * i < MAXN; ++i) {
    if (!sieve[i]) {
      sieve[i] = i;
      for (int j = i * i; j < MAXN; j += i) {
        sieve[j] = i;
      }
    }
  }

  for (int i = 0; i < MAXN; ++i) {
    if (!sieve[i]) {
      sieve[i] = i; // divisor is a prime
    }
  }
}

void print_ans(std::initializer_list<int>&& l) {
  cout << l.size() << "\n";
  for (auto el: l) {
    cout << el << " ";
  }
  cout << "\n";
}

void solve() {
  string s;
  char c;
  int n;
  cin >> n >> c;
  cin >> s;
  vector<int> elements;
  for (int i = 0; i < n; ++i) {
    if (s[i] != c) {
      elements.push_back(i + 1);
    }
  }

  if (elements.empty()) {
    cout << "0\n";
    return;
  }

  // factorize elements;
  map<int, int> unique_factors_cnt;
  for (auto el: elements) {
    while (el != 1) {
      int p = sieve[el];
      while (el % p == 0) {
        el /= p;
      }
      unique_factors_cnt[p]++;
    }
  }

  set<int> factors_all_got;
  for (auto [p, cnt]: unique_factors_cnt) {
    if (cnt == elements.size()) {
      factors_all_got.insert(p);
    }
  }

  // find any prime not in factors
  for (int i = 2; i <= n; ++i) {
    // try to find prime no one got
    if (i > n / 2 && s[i - 1] == c) {
      print_ans({i});
      return;
    }

    if (sieve[i] == i) {
      if (!unique_factors_cnt.count(i)) {
        print_ans({i});
        return;
      }
    }
  }

  print_ans({n - 1, n});
}

int main() {
  init_sieve();
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}

